dnl Setup autoconf
AC_INIT([STHBTMAKER], [0.1], [coffe92@gmail.com])
dnl AM_INIT_AUTOMAKE

dnl debug option
AC_ARG_ENABLE(debug,
              AS_HELP_STRING([--enable-debug],[enable debugging, defult: no]),
              [case "${enableval}" in
               yes) debug = true  ;;
               no)  debug = false ;;
               *)   AC_MSG_ERROR([bad value ${enablevalue} for --enable-debug]) ;;
             esac], [debug=false])
dnl Check dependences
echo "Cheking dependences"
AC_LANG(C++)
dnl disable all CXXFLAGS if it was not declarated
if [test -z $CXXFLAGS; ] then
  if test x"${debug}" == x"true"; then
    CXXFLAGS="-g -O0"
  else
    CXXFLAGS="-O2"
  fi
fi
AC_PROG_CXX

AC_CHECK_PROG(ROOT_CHECK,root,yes)
if test x"$ROOT_CHECK" != x"yes" ; then
    AC_MSG_ERROR([Please install ROOT before installing.])
fi

dnl Configure Makefile from Makefile.in
AC_OUTPUT(Makefile.gen)
