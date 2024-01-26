#!/bin/sh

#问卷调查
gdialog --title "问卷调查" --msgbox "欢迎参与简单问卷调查" 9 18
gdialog --title "确认" --yesno "请问阁下参与与否？" 9 18
if [ $? != 0 ]; then
	gdialog --infobox "谢谢您！" 5 20
	sleep 2
	gdialog --clear
	exit 0
fi

gdialog --title "问卷调查" --inputbox "请输入生辰八字" 9 30 2>_1.txt
Q_NAME=$(cat _1.txt)

gdialog --menu "$Q_NAME，喜欢什么曲风？ 15 30 4 1 "古典" 2 "爵士" 3 "国家" 4 "其它" 2>_1.txt
Q_MUSIC=$(cat _1.txt)

if [ "$Q_MUSIC" = "1" ]; then
	gdialog --title "喜欢古典" --msgbox "选对了！" 12 25
else
	gdialog --title "不喜欢古典" --msgbox "自取其辱！" 12 25
fi
sleep 2
gdialog --clear
exit 0
