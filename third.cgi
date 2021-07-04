#!/bin/sh
# printenv.cgi
# вывод на печать настроек Web–сервера с помощью команды env
echo "Content-type: text/html"
echo ""
echo "<HR>"
echo "<HTML><PRE>"
env
echo "</PRE></HTML>"
# печатание календаря 
echo "<HR>"
echo "<HTML><PRE>"
cal
echo "</PRE></HTML>"
echo "<HR>"

