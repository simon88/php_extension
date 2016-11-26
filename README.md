# Php extension

This simple extension, take 2 arguments, first is the name of the file and second is buffer size.
This simple extension read file and create simple object with two property :
- First propety is the number of line
- Second is an array of line

## How compile

On linux you need php5-dev, to install use this command line : `apt-get install php5-dev`
```
phpize5
./configure
make
```

After `make` command new folder is create, name is "modules", in this folder you can find .so file, this file is the nex extension.

Next step, load new extension, move in modules folder :
```
echo extension=`pwd`/myext.so >/etc/php5/mods-available/myext.ini
php5enmod myext
/etc/init.d/apache2 restart
```

## How to test

Create php file and txt file with some lines. And add this line in your php file
```
<?php

var_dump("file.txt", 1024);
```

Enjoy, you have new object with an `array` containing all the lines and the number of lines !


