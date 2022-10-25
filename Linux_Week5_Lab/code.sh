#/bin/bash

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

#build files and folder
touch missing_list 
touch wrong_list
cd compressed_files
mkdir zip/
mkdir rar/
mkdir tar.gz/
mkdir unknown/
cd ..

#read line from student_id
cat filename student_id | while read line
do
    path=`find /home/webbertang/Linux_Week5_Lab/compressed_files -name "*$line*"`
    extension=$(echo $path | cut -d"." -f 2)
    if [ -z $path ]
    then
        echo $line >> missing_list
    else
        if [ "$extension" = "zip" ]; then
            cd compressed_files
            unzip $line.zip -d /home/webbertang/Linux_Week5_Lab/compressed_files/zip
            cd ..
        elif [ "$extension" = "rar" ]; then
            cd compressed_files
            unrar x $line.rar /home/webbertang/Linux_Week5_Lab/compressed_files/rar
            cd ..
        elif [ "$extension" = "tar" ]; then
            cd compressed_files
            tar -zxvf $line.tar.gz -C /home/webbertang/Linux_Week5_Lab/compressed_files/tar.gz
            cd ..
        else
            echo $line >> wrong_list
        fi
    fi
done
