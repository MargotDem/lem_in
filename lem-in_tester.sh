#!/bin/bash

#add system("leaks lem-in >> leaks.txt") before return in main
#add system("leaks lem-in >> error_leaks.txt") before exit(1)

noir='\e[0;30m'
gris='\e[1;30m'
rougefonce='\e[0;31m'
rose='\e[1;31m'
vertfonce='\e[0;32m'
vertclair='\e[1;32m'
orange='\e[0;33m'
jaune='\e[1;33m'
bleufonce='\e[0;34m'
bleuclair='\e[1;34m'
violetfonce='\e[0;35m'
violetclair='\e[1;35m'
cyanfonce='\e[0;36m'
cyanclair='\e[1;36m'
grisclair='\e[0;37m'
blanc='\e[1;37m'

neutre='\e[0;m'
underline='\e[4m'
bold='\033[1m'
italic='\e[3m'

pwd=$(pwd)

declare -a map
declare -a your_line
declare -a ref_line
declare -a ref_leaks
declare -a diff_arr
declare -a time_arr

clean () {
    if [ -e $pwd/lem-in_test ];then
        rm -rf $pwd/lem-in_test
    fi
}

save_leaks () {
    if [ -e $pwd/int_leaks.txt ];then
        int_leaks=$(grep "leaked bytes" $pwd/int_leaks.txt | cut -d ' ' -f 3)
        if [ $int_leaks -ne 0 ]; then
            cp $pwd/int_leaks.txt $pwd/lem-in_test/$strmap/mid_leaks.txt
        fi
    fi
    if [ -e $pwd/exit_s_leaks.txt ];then
        exit_solver=$(grep "leaked bytes" $pwd/exit_s_leaks.txt | cut -d ' ' -f 3)
        if [ $exit_solver -ne 0 ]; then
            cp $pwd/exit_p_leaks.txt $pwd/lem-in_test/$strmap/exit_solver_leaks.txt
        fi
    fi
    if [ -e $pwd/exit_p_leaks.txt ];then
        exit_parsing=$(grep "leaked bytes" $pwd/exit_p_leaks.txt | cut -d ' ' -f 3)
        if [ $exit_parsing -ne 0 ]; then
            cp $pwd/exit_p_leaks.txt $pwd/lem-in_test/$strmap/exit_parsing_leaks.txt
        fi
    fi
}

set_data_leaks () {
     if [ -e $1 ];then
        process_line=$(grep "leaked bytes" $1)
        leak=$(grep "leaked bytes" $1 | cut -d ' ' -f 3)
        else
        process_line="N/A"
        leak="N/A"
     fi
}

save_arr () {
    map=( "${map[@]}" "$1" )
    your_line=( "${your_line[@]}" "$2" )
    ref_line=( "${ref_line[@]}" "$3" )
    ref_leak=( "${ref_leak[@]}" "$4" )
    diff_arr=( "${diff_arr[@]}" "$5" )
    time_arr=( "${time_arr[@]}" "$6" )
}


display_error () {
    printf "We found an Error in $1\n"
}

set_data_line () {
        line_required=$(grep "lines required" $1 | cut -d' ' -f 8 | head -n 1)
        line_founded=$(grep "^L" $1 | wc -l | awk '{gsub(/^[ \t]+| [ \t]+$/,""); print$0, ""}')
}


display () {
    printf "In map $1\n"
    printf "Your returned ${orange}${underline}${bold}$2${neutre} lines and the required line is ${cyanfonce}${underline}${bold}$3${neutre}\n"
    max=5
    max=$(($3 + 5))
    min=$(($3 - 5))
    printf "You have a diffence of "
    if [ $2 -ge $max ]; then
        printf "${rougefonce}${bold}"
    elif [ $2 -le $min ]; then
        printf "${rougefonce}${bold}"
    else
        printf "${vertfonce}${bold}"
    fi
    printf "$diff${neutre} lines.\n"
}

display_leaks () {
     if [ -e $3 ];then
        printf "We found "
        if [ "$1" -ne "0" ]; then
            printf "${rougefonce}${bold}"
            cp $pwd/leaks.txt $pwd/lem-in_test/$strmap/leaks.txt
        else
            printf "${vertfonce}${bold}"   
        fi
        printf "$1${neutre} leaks from your program.\n"
        printf "\t${italic}$2${neutre}\n\n"
        else
        printf "Leaks: N/A.\nYou need to insert at your exit point the command:\n${italic}system(\"leaks exec > leaks.txt\")\n"
     fi
}

display_time () {
    printf "It took ${italic}${bleuclair}${time}${neutre} to find a solution.\n"
}

save_time () {
    if [ -e $pwd/lem-in_test/$strmap/ref_time.txt ];then
        time=$(grep "user" $pwd/lem-in_test/$strmap/ref_time.txt | cut -c6-)
        else
        time="N/A"
    fi
}

clean

mkdir -p $pwd/lem-in_test
mkdir -p $pwd/lem-in_test/time

for MAP in $(find ./test_maps -type f);
do
    result=$(grep ".txt" <<< "$MAP")
    if [ -n "$result" ]; then
        strmap=$(echo $result | rev | cut -d'/' -f 1| rev)
        mkdir -p $pwd/lem-in_test/$strmap
        ./lem-in < $MAP &> $pwd/lem-in_test/$strmap/out_put.txt
        foo=$( { time ./lem-in < $MAP &> /dev/null 2> /dev/null ; } 2>$pwd/lem-in_test/$strmap/ref_time.txt )
        save_time $strmap
        save_leaks
        error=$(grep -i "ERROR" $pwd/lem-in_test/$strmap/out_put.txt)
        if [ $error ]; then
            set_data_leaks $pwd/exit_leaks.txt
            save_arr "$strmap" "Error" "Error" $leak "0" "$time"
            if [ "$1" = '-v' ]; then
                display_error "$strmap"
                display_leaks $leak "$process_line" $pwd/exit_leaks.txt
            fi
        else
            set_data_line "$pwd/lem-in_test/$strmap/out_put.txt"
            if [[ $line_required ]]; then
                if (( $line_required == $line_founded ));then
                    diff=0
                else
                    if (( $line_required > $line_founded ));then
                        diff=$(($line_required - $line_founded))
                    else
                        diff=$(($line_founded - $line_required))
                    fi
                fi
            else
                line_required=0
                diff=0
            fi
            set_data_leaks $pwd/leaks.txt
            if [ "$1" = '-v' ]; then
                display $strmap $line_founded $line_required
                display_time "$time"
                display_leaks $leak "$process_line" $pwd/leaks.txt
            fi
            save_arr "$strmap" "$line_founded" "$line_required" $leak $diff $time
        fi
    fi
done
i=0
size=${#your_line[*]}
printf "Summary: \n"

option="MAP NAME"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "40" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

option="SOL"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "6" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

option="REF"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "6" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

option="DIFF"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "6" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

option="LEAKS"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "8" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

option="TIME"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "10" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

option="RESULTS"
printf "| ${bold}${option}"
strsize=${#option}
while [ "$strsize" -lt "10" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done
printf "|${neutre}\n"

while [ "$i" -lt "$size" ]
do
printf "| ${bold}${map[i]}${neutre}"
strsize=${#map[i]}
while [ "$strsize" -lt "40" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

printf "| ${your_line[i]}"
strsize=${#your_line[i]}
while [ "$strsize" -lt "6" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

printf "| ${ref_line[i]}"
strsize=${#ref_line[i]}
while [ "$strsize" -lt "6" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

printf "| "
if [ "${diff_arr[i]}" -gt "5" ]; then
    printf "${rougefonce}${bold}"  
else
    printf "${vertfonce}${bold}"
fi 
printf "${diff_arr[i]}${neutre}"
strsize=${#diff_arr[i]}
while [ "$strsize" -lt "6" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

printf "| "
if [ "${ref_leak[i]}" -eq "0" ]; then
    printf "${vertfonce}${bold}"
else
    printf "${rougefonce}${bold}" 
fi
printf "${ref_leak[i]}${neutre}"
strsize=${#ref_leak[i]}
while [ "$strsize" -lt "8" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

printf "| ${italic}${time_arr[i]}${neutre}"
strsize=${#time_arr[i]}
while [ "$strsize" -lt "10" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done

if [ "${diff_arr[i]}" -le "5" ]; then
    if [ "${ref_leak[i]}" -eq "0" ]; then
        ret="SUCCESS"
        else
        ret="FAIL"
    fi
else
    ret="FAIL"
fi
if [ "$ret" = "SUCCESS" ]; then
    printf "| ${vertfonce}${bold}"
else
    printf "| ${rougefonce}${bold}"  
fi
printf "${ret}${neutre}"
strsize=${#ret}
while [ "$strsize" -lt "10" ];do
    printf " "
    strsize=$(( $strsize + 1 ))
done
printf "|\n"
i=$(( i + 1 ))
done
rm -rf exit_p_leaks.txt
rm -rf exit_s_leaks.txt
rm -rf exit_leaks.txt
rm -rf int_leaks.txt
rm -rf leaks.txt