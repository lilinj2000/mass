#! /bin/sh

home_app=~/app

home_mass=${home_app}/mass

./configure --prefix=${home_mass}

if test -d ${home_mass}; then
    rm -rf ${home_mass}
fi

make install

make distclean
