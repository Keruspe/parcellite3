/* Copyright (C) 2007-2008 by Xyhthyx <xyhthyx@gmail.com>
 *
 * This file is part of Parcellite.
 *
 * Parcellite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Parcellite is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <gtk/gtk.h>
#include "main.h"
#include "utils.h"
#include "history.h"

GSList* history;

/* Reads history from ~/.local/share/parcellite/history */
void
read_history ()
{
  /* Build file path */
  gchar* history_path = g_build_filename(g_get_home_dir(),
                                         HISTORY_FILE,
                                         NULL);
  /* Open the file for reading */
  FILE* history_file = fopen(history_path, "rb");
  g_free(history_path);
  /* Check that it opened and begin read */
  if (history_file)
  {
    /* Read the size of the first item */
    gint size;
    fread(&size, 4, 1, history_file); 
    /* Continue reading until size is 0 */
    while (size)
    {
      /* Malloc according to the size of the item */
      gchar* item = (gchar*)g_malloc(size + 1);
      /* Read item and add ending character */
      fread(item, size, 1, history_file);
      item[size] = '\0';
      /* Prepend item and read next size */
      history = g_slist_prepend(history, item);
      fread(&size, 4, 1, history_file);
    }
    /* Close file and reverse the history to normal */
    fclose(history_file);
    history = g_slist_reverse(history);
  }
}

/* Saves history to ~/.local/share/parcellite/history */
void
save_history()
{
  /* Check that the directory is available */
  check_dirs();
  /* Build file path */
  gchar* history_path = g_build_filename(g_get_home_dir(),
                                         HISTORY_FILE,
                                         NULL);
  /* Open the file for writing */
  FILE* history_file = fopen(history_path, "wb");
  g_free(history_path);
  /* Check that it opened and begin write */
  if (history_file)
  {
    GSList* element;
    /* Write each element to a binary file */
    for (element = history; element != NULL; element = element->next)
    {
      /* Create new GString from element data, write its length (size)
       * to file followed by the element data itself
       */
      GString* item = g_string_new((gchar*)element->data);
      fwrite(&(item->len), 4, 1, history_file);
      fputs(item->str, history_file);
      g_string_free(item, TRUE);
    }
    /* Write 0 to indicate end of file */
    gint end = 0;
    fwrite(&end, 4, 1, history_file);
    fclose(history_file);
  }
}

/* Adds item to the end of history */
void
append_item(gchar* item)
{
  if (item)
  {
    /* Prepend new item */
    history = g_slist_prepend(history, g_strdup(item));
    /* Shorten history if necessary */
    GSList* last_possible_element = g_slist_nth(history, prefs.history_limit - 1);
    if (last_possible_element)
    {
      /* Free last posible element and subsequent elements */
      g_slist_free(last_possible_element->next);
      last_possible_element->next = NULL;
    }
    /* Save changes */
    if (prefs.save_history)
      save_history();
  }
}

/* Truncates history to history_limit items */
void
truncate_history()
{
  if (history)
  {
    /* Shorten history if necessary */
    GSList* last_possible_element = g_slist_nth(history, prefs.history_limit - 1);
    if (last_possible_element)
    {
      /* Free last posible element and subsequent elements */
      g_slist_free(last_possible_element->next);
      last_possible_element->next = NULL;
    }
    /* Save changes */
    if (prefs.save_history)
      save_history();
  }
}

/* Returns pointer to last item in history */
gpointer
get_last_item()
{
  if (history)
  {
    if (history->data)
    {
      /* Return the last element */
      gpointer last_item = history->data;
      return last_item;
    }
    else
      return NULL;
  }
  else
    return NULL;
}
