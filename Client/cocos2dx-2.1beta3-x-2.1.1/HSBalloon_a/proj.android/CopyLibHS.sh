#!/bin/bash
src_dir="/cygdrive/f/Work/IOS/Client/cocos2d-2.1beta3-x-2.1.1/cocos2d-2.1beta3-x-2.1.1/libHS/proj.win32"
dest_dir="/cygdrive/f/Work/IOS/Client/cocos2d-2.1beta3-x-2.1.1/cocos2d-2.1beta3-x-2.1.1/HSBalloon_a/Classes"
suffix_name="cpp h"
function scandir() {
    local cur_dir parent_dir workdir dest_cur_dir
	#workdir is  processed dir
    workdir=$1
    cd ${workdir}
    if [ ${workdir} = "/" ]
    then
        cur_dir=""
    else
        cur_dir=$(pwd)
		dest_cur_dir=`echo "$cur_dir"|awk -v s=$src_dir -v d=$dest_dir -v c=$cur_dir 'BEGIN{gsub(s,d,c);print c}'`
		if [ ! -d "$dest_cur_dir" ];then
			mkdir -m 755 -p "${dest_cur_dir}"
	    fi
    fi
 
    for dirlist in $(ls ${cur_dir})
    do
        if [ -d ${dirlist} ];then
            cd ${dirlist}
			if [ ! -d "${dest_cur_dir}/${dirlist}" ];then
				mkdir -m 755 -p "${dest_cur_dir}/${dirlist}"
			fi
			#recursion find child dir
            scandir ${cur_dir}/${dirlist}
            cd ..
        else
			file_name=${cur_dir}/${dirlist}
			ext=${file_name##*.}
			#copy specify file to dest dir
			for e in $suffix_name 
			do
				if [ "$e" == "$ext" ];then
					echo "${dest_cur_dir}/${dirlist}"
            		cp ${cur_dir}/${dirlist} ${dest_cur_dir}/${dirlist}
			    fi
			done
        fi
    done
}
if [ ! -d "${src_dir}" ];then
	echo "please input src dir correctly!"
	exit 1
fi
if [ ! -d "${dest_dir}" ];then
	mkdir -p ${dest_dir}
fi
scandir ${src_dir}