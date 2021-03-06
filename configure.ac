# -------------------------------------------------------------------------------
# Autoconf/automake.
# -------------------------------------------------------------------------------
AC_PREREQ([2.5])
AC_INIT([parcellite], [scm], [Marc-Antoine@Perennou.com])
AM_INIT_AUTOMAKE([AC_PACKAGE_TARNAME()], [AC_PACKAGE_VERSION()])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([src/main.c])
AM_CONFIG_HEADER([config.h])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# -------------------------------------------------------------------------------
# Gettext.
# -------------------------------------------------------------------------------

GETTEXT_PACKAGE=parcellite
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [gettext package])

ALL_LINGUAS="cs da de es fr hu it ja nb pl pl_PL pt_BR ro ru sv tr zh_CN"
AM_GLIB_GNU_GETTEXT()
AC_PROG_INTLTOOL([0.23])

parcellitelocaledir='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(parcellitelocaledir)

AM_GNU_GETTEXT([external])

# -------------------------------------------------------------------------------
# Main settings.
# -------------------------------------------------------------------------------
# prefix=/usr

# -------------------------------------------------------------------------------
# Checks for programs.
# -------------------------------------------------------------------------------
AC_PROG_CC()
AC_PROG_INSTALL()
AC_PROG_MAKE_SET()

# -------------------------------------------------------------------------------
# Checks for libraries.
# -------------------------------------------------------------------------------
AM_PATH_GTK_3_0(2.99.0, [], AC_MSG_ERROR(Requirement not met: gtk >= 2.99.0))
AM_PATH_GLIB_2_0(2.14.0, [], AC_MSG_ERROR(Requirement not met: glib >= 2.14.0))

# -------------------------------------------------------------------------------
# Checks for header files.
# -------------------------------------------------------------------------------
AC_CHECK_HEADERS([stdlib.h string.h pthread.h])

# -------------------------------------------------------------------------------
# Checks for typedefs, structures, and compiler characteristics.
# -------------------------------------------------------------------------------
AC_C_CONST()

# -------------------------------------------------------------------------------
# Checks for library functions.
# -------------------------------------------------------------------------------
AC_TYPE_SIGNAL()

AC_CONFIG_FILES([Makefile 
                 doc/Makefile
                 src/Makefile
                 data/Makefile])

AC_OUTPUT()

