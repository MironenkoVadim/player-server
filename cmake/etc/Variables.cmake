set(ORGANIZATION_NAME "RTIS")
set(AUTHOR_NAME "Кристина Морозова")

set(DOXYGEN_PROJECT_TITLE "Database admin server")
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_GENERATE_HTML YES)

set(CPACK_GENERATOR "TXZ;DEB")
set(CPACK_PACKAGE_CONTACT "Кристина Морозова <dima_hanabusa@mail.ru>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Database admin server")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_SOURCE_IGNORE_FILES
    .git/
    obj.*/
    build
    files/var
    debian/tmp/
    debian/files
    debian/.*\\\\.log$
    debian/.*.substvars
    debian/stamp.*
    CMakeLists.txt.user
    cmake/lib/.git$
    ~$
    \\\\..*\\\\.swp$)
