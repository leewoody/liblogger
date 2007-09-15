# Script to generate the documentation.
ln -s ../src/inc/liblogger
ln -s ../src/testapp
rm ./docs/html/*
doxygen
cp ./docs/tree.html ./docs/html/
