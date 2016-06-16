#!/bin/bash
default_ai=./Release/middle_ages
gui=sredniowiecze_gui_linux64_v1/sredniowiecze_gui_with_libs.sh
gui_in=3
gui_out=4
ai1_in=5
ai1_out=6
ai2_in=7
ai2_out=8

#Czytamy argumenty w case'ie
while [ "$#" -ge 1 ]
do
  key="$1"
  case $key in
      -n)
      board_size="$2"
      shift
      ;;
      -k)
      turns="$2"
      shift
      ;;
      -s)
      waiting_time="$2"
      shift
      ;;
      -p1)
      xy1="$2"
      shift
      ;;
      -p2)
      xy2="$2"
      shift
      ;;
      -ai1)
      ai1="$2"
      shift
      ;;
      -ai2)
      ai2="$2"
      shift
      ;;
      *)
      exit 1;
      ;;
  esac
  shift
done

#Jesli nie bylo argumentu -n, to rozmiar planszy to 10
if [ -z "$board_size" ];
then
  board_size=10
elif ! [ $board_size -eq $board_size ];
then
  exit 1;
elif [ $(($board_size < 9)) -eq 1 ];
then
  exit 1;
fi

#Jesli nie bylo argumentu -k, to liczba tur to 100
if [ -z "$turns" ];
then
  turns=100
elif ! [ $turns -eq $turns ];
then
  exit 1;
fi

#Jesli nie bylo argumentu -s, to czas oczekiwania to 1 sekunda
if [ -z "$waiting_time" ];
then
  waiting_time=1
elif ! [ $waiting_time -eq $waiting_time ];
then
  exit 1
fi

#Pomocnicze zmienne do wyznaczania krancow losowania
lower_x_limit=1
lower_y_limit=1
upper_y_limit=$board_size;
upper_x_limit=$(($board_size - 3));

#Sprawdzamy, czy byly dane poczatkowe pola, a jak nie, to losujemy
if [ -z "$xy1" -a -z "$xy2" ];
then
  x1=$(shuf -i $lower_x_limit'-'$upper_x_limit -n '1');
  y1=$(shuf -i $lower_y_limit'-'$upper_y_limit -n '1');
  if [ $(($x1 + 11 <= $board_size)) == '1' -o $(($y1 + 8 <= $board_size)) == '1' ];
  then
    if [ $(($x1 + 11 <= $board_size)) == '1' ];
    then
      lower_x_limit=$(($x1 + 8));
      upper_x_limit=$(($board_size - 3));
    else
      lower_y_limit=$(($y1 + 8));
    fi
    first_randomization=true
  else
    if [ $(($x1 - 8 > 0)) == '1' -o $(($y1 - 8 > 0)) == '1' ];
    then
      if [ $(($x1 - 8 >= 0)) == '1' ];
      then
        upper_x_limit=$(($x1 - 8));
      else
        upper_y_limit=$(($y1 - 8));
      fi
      first_randomization=true
    else
      first_randomization=false
    fi
  fi
  while [ $first_randomization == 'false' ];
  do
    x1=$(shuf -i $lower_x_limit'-'$upper_x_limit -n '1');
    y1=$(shuf -i $lower_y_limit'-'$upper_y_limit -n '1');
    if [ $(($x1 + 11 <= $board_size)) == '1' -o $(($y1 + 8 <= $board_size)) == '1' ];
    then
      if [ $(($x1 + 11 <= $board_size)) == '1' ];
      then
        lower_x_limit=$(($x1 + 8));
        upper_x_limit=$(($board_size - 3));
      else
        lower_y_limit=$(($y1 + 8));
      fi
      first_randomization=true
    else
      if [ $(($x1 - 8 > 0)) == '1' -o $(($y1 - 8 > 0)) == '1' ];
      then
        if [ $(($x1 - 8 > 0)) == '1' ];
        then
          upper_x_limit=$(($x1 - 8));
        else
          upper_y_limit=$(($y1 - 8));
        fi
        first_randomization=true
      else
        first_randomization=false
      fi
    fi
  done
  if [ $upper_x_limit -lt $lower_x_limit -o $upper_y_limit -lt $lower_y_limit ];
  then
    exit 1
  fi
  x2=$(shuf -i $lower_x_limit'-'$upper_x_limit -n '1');
  y2=$(shuf -i $lower_y_limit'-'$upper_y_limit -n '1');
elif [ -z "$xy1" ];
then
  IFS=', ' read -r -a array <<< "$xy2";
  x2=${array[0]}
  if [ $x2 -lt $lower_x_limit -o $x2 -gt $upper_x_limit ];
  then
    exit 1;
  fi
  y2=${array[1]}
  if [ $y2 -lt $lower_y_limit -o $y2 -gt $upper_y_limit ];
  then
    exit 1;
  fi
  if [ $(($x2 - 8)) -lt $lower_x_limit -a $(($x2 + 8)) -gt $upper_x_limit ];
  then
    if [ $(($y2 - 8)) -lt $lower_y_limit -a $(($y2 + 8)) -gt $upper_y_limit ];
    then
    exit 1
    fi
  fi
  if [ $(($x2 + 11 <= $board_size)) == '1' -o $(($y2 + 8 <= $board_size)) == '1' ];
  then
    if [ $(($x2 + 11 <= $board_size)) == '1' ];
    then
      lower_x_limit=$(($x2 + 8));
      upper_x_limit=$(($board_size - 3));
    else
      lower_y_limit=$(($y2 + 8));
    fi
  else
    if [ $(($x2 - 8 > 0)) == '1' -o $(($y2 - 8 > 0)) == '1' ];
    then
      if [ $(($x2 - 8 >= 0)) == '1' ];
      then
        upper_x_limit=$(($x2 - 8));
      else
        upper_y_limit=$(($y2 - 8));
      fi
    fi
  fi
  if [ $upper_x_limit -lt $lower_x_limit -o $upper_y_limit -lt $lower_y_limit ];
  then
    exit 1
  fi
  x1=$(shuf -i $lower_x_limit'-'$upper_x_limit -n '1');
  y1=$(shuf -i $lower_y_limit'-'$upper_y_limit -n '1');
elif [ -z "$xy2" ];
then
  IFS=', ' read -r -a array <<< "$xy1"
  x1=${array[0]}
  if [ $x1 -le $lower_x_limit -o $x1 -ge $upper_x_limit ];
  then
    exit 1;
  fi
  y1=${array[1]}
  if [ $y1 -le $lower_y_limit -o $y1 -ge $upper_y_limit ];
  then
    exit 1;
  fi
  if [ $(($x1 - 8)) -lt $lower_x_limit -a $(($x1 + 8)) -gt $upper_x_limit ];
  then
    if [ $(($y1 - 8)) -lt $lower_y_limit -a $(($y1 + 8)) -gt $upper_y_limit ];
    then
    exit 1
    fi
  fi
  if [ $(($x1 + 11 <= $board_size)) == '1' -o $(($y1 + 8 <= $board_size)) == '1' ];
  then
    if [ $(($x1 + 11 <= $board_size)) == '1' ];
    then
      lower_x_limit=$(($x1 + 8));
      upper_x_limit=$(($board_size - 3));
    else
      lower_y_limit=$(($y1 + 8));
    fi
  else
    if [ $(($x1 - 8 > 0)) == '1' -o $(($y1 - 8 > 0)) == '1' ];
    then
      if [ $(($x1 - 8 >= 0)) == '1' ];
      then
        upper_x_limit=$(($x1 - 8));
      else
        upper_y_limit=$(($y1 - 8));
      fi
    fi
  fi
  if [ $upper_x_limit -lt $lower_x_limit -o $upper_y_limit -lt $lower_y_limit ];
  then
    exit 1
  fi
  x2=$(shuf -i $lower_x_limit'-'$upper_x_limit -n '1');
  y2=$(shuf -i $lower_y_limit'-'$upper_y_limit -n '1');
else
  IFS=', ' read -r -a array1 <<< "$xy1";
  x1=${array1[0]}
  y1=${array1[1]}
  IFS=', ' read -r -a array2 <<< "$xy2";
  x2=${array2[0]}
  y2=${array2[1]}
  if [ $(($x1 - $x2 < 8)) == '1' -a $(($x2 - $x1 < 8)) == '1' ] && [ $(($y1 - $y2 < 8)) == '1' -a $(($y2 - $y1 < 8)) == '1' ];
  then
    exit 1;
  fi
fi

#Inicjujemy protokoly komunikacji dla ai
if [ -z "$ai1" ];
then
  human1=true
elif [ ! -x "$ai1" ];
then
  exit 1;
else
  pipe=$(mktemp -u)
  mkfifo $pipe
  eval "exec ${ai1_in}<>${pipe}"
  rm $pipe
  pipe=$(mktemp -u)
  mkfifo $pipe
  eval "exec ${ai1_out}<>${pipe}"
  rm $pipe
fi
if [ -z "$ai2" ];
then
  human2=true
elif [ ! -x "$ai2" ];
then
  exit 1;
else
  pipe=$(mktemp -u)
  mkfifo $pipe
  eval "exec ${ai2_in}<>${pipe}"
  rm $pipe
  pipe=$(mktemp -u)
  mkfifo $pipe
  eval "exec ${ai2_out}<>${pipe}"
  rm $pipe
fi

#Inicjalizujemy napisy inicjalizacyjne
init1="INIT $board_size $turns 1 $x1 $y1 $x2 $y2"
init2="INIT $board_size $turns 2 $x1 $y1 $x2 $y2"

#Inicjujemy protokol komunikacji dla gui
pipe=$(mktemp -u)
mkfifo $pipe
eval "exec ${gui_in}<>${pipe}"
rm $pipe
pipe=$(mktemp -u)
mkfifo $pipe
eval "exec ${gui_out}<>${pipe}"
rm $pipe

#Uruchamiamy gui i stosowne ai
if [ ! -z "$human1" -a ! -z "$human2" ];
then
  #Uruchomienie gui dla dwoch ludzi
  ./$gui -human1 -human2 <&${gui_in} >&${gui_out} &
  pid_gui=$!
  #Inicjalizacja gui dla dwoch ludzi
  echo $init1 >&${gui_in};
  echo $init2 >&${gui_in};
  #Czekanie, az gui sie skonczy
  sleep $waiting_time
  wait $pid_gui;
  exit_code=$?
  if [ $exit_code -ne 0 ];
  then
    exit 1;
  else
    exit 0;
  fi
elif [ -z "$human1" -a ! -z "$human2" ];
then
  #Uruchomienie gui dla ludzia i ai
  ./$gui -human2 <&${gui_in} >&${gui_out} &
  pid_gui=$!
  #Uruchomienie ai
  $ai1 <&${ai1_in} >&${ai1_out} &
  pid_ai=$!
  #Zainicjalizowanie ai
  echo $init1 >&${ai1_in};
  #Zainicjalizowanie gui
  echo $init1 >&${gui_in};
  echo $init2 >&${gui_in};
  gui_playing=1
  ai_playing=1
  turn=1
  while [ "$gui_playing" -eq 1 -a "$ai_playing" -eq 1 ];
  do
    if ! kill -0 $pid_ai; then
      ai_playing=0
      #break
    fi
    if ! kill -0 $pid_gui; then
      gui_playing=0
      #break
    fi
    if [ "$turn" -eq 1 ];
    then
      #player 1
      read -t 0.4 line <&${ai1_out}
      if ! kill -0 $pid_ai; then
        ai_playing=0
        #break
      fi
      if [ "$line" == "" ];
      then
        :
      elif [[ "$line" =~ END_TURN ]];
      then
        #end turn 1
        turn=2
        #sending to gui
        echo $line
        echo $line >&${gui_in}
        if ! kill -0 $pid_gui; then
          gui_playing=0
          #break
        fi
        sleep $waiting_time
      else
        #sending to gui
        echo $line
        echo $line >&${gui_in}
        if ! kill -0 $pid_gui; then
          gui_playing=0
          #break
        fi
      fi
    else
      read -t 0.4 line <&${gui_out}
      if ! kill -0 $pid_gui; then
        gui_playing=0
        #break
      fi
      if [[ "$line" =~ END_TURN ]];
      then
        #end turn 2
        turn=1
        #sending to ai1
        echo $line
        echo $line >&${ai1_in}
        if ! kill -0 $pid_ai; then
          ai_playing=0
          #break
        fi
        sleep $waiting_time
      elif [ "$line" != ""  ];
      then
        #sending to ai1
        echo $line
        echo $line >&${ai1_in}
        if ! kill -0 $pid_ai; then
          ai_playing=0
          #break
        fi
      else
        :
      fi
    fi
    if ! kill -0 $pid_ai; then
      ai_playing=0
      #break
    fi
    if ! kill -0 $pid_gui; then
      gui_playing=0
      #break
    fi
  done
  if [ $ai_playing == 0 ];
  then
    wait $pid_ai
    ai_code=$?
    if (($ai_code > 2));
    then
      #"Ai wywalilo blad"
      wait $pid_gui
      exit 1
    else
      #"Ai poprawnie sie skonczylo"
      wait $pid_gui
      gui_code=$?
      if [ $gui_code == 0 ];
      then
        #"Gui tez poprawnie sie skonczylo"
        exit 0
      else
        #"Gui niepoprawnie sie skonczylo"
        exit 1
      fi
    fi
  fi
  if [ $gui_playing == 0 ];
  then
    wait $pid_gui
    gui_code=$?
    if [ $gui_code == 0 ];
    then
      #"Gui poprawnie sie skonczylo"
      if kill -0 pid_ai;
      then
        wait $pid_ai
        ai_code=$?
        if (( $ai_code > 2 ));
        then
          #"Ai jednak wywalilo sie"
          exit 1
        else
          #"Ai tez poprawnie sie skonczylo"
          exit 0
        fi
      fi
    else
      if kill -0 $pid_ai;
      then
        kill $pid_ai
      fi
      #"Gui wywalilo sie"
      exit 1
    fi
  fi
elif [ ! -z "$human1" -a -z "$human2" ];
then
  #Uruchomienie gui dla ludzia i ai
  ./$gui -human1 <&${gui_in} >&${gui_out} &
  pid_gui=$!
  #Uruchomienie ai
  $ai2 <&${ai2_in} >&${ai2_out} &
  pid_ai=$!
  #Zainicjalizowanie gui
  echo $init1 >&${gui_in};
  echo $init2 >&${gui_in};
  #Zainicjalizowanie ai
  echo $init2 >&${ai2_in};
  gui_playing=1
  ai_playing=1
  turn=1
  while [ "$gui_playing" -eq 1 -a "$ai_playing" -eq 1 ];
  do
    if ! kill -0 $pid_ai;
    then
      ai_playing=0
      #break
    fi
    if ! kill -0 $pid_gui;
    then
      gui_playing=0
      #break
    fi
    if [ "$turn" -eq 1 ];
    then
      #"player 1"
      read -t 0.4 line <&${gui_out}
      if ! kill -0 $pid_gui;
      then
        gui_playing=0
        #break
      fi
      if [ "$line" == "" ];
      then
        :
      elif [[ "$line" =~ END_TURN ]];
      then
        #end turn 1
        #"sending to ai"
        turn=2
        echo $line >&${ai2_in}
        if ! kill -0 $pid_ai;
        then
          ai_playing=0
          #break
        fi
        sleep $waiting_time
      else
        #"sending to ai"
        echo $line >&${ai2_in}
        if ! kill -0 $pid_ai;
        then
          ai_playing=0
          #break
        fi
      fi
    else
      #"player 2"
      read -t 0.4 line <&${ai2_out}
      if ! kill -0 $pid_ai;
      then
        ai_playing=0
        #break
      fi
      if [[ "$line" =~ END_TURN ]];
      then
        #"end turn 2"
        turn=1
        #"sending to gui"
        echo $line >&${gui_in};
        if ! kill -0 $pid_gui;
        then
          gui_playing=0
          #break
        fi
        sleep $waiting_time
      elif [ "$line" != ""  ];
      then
        #"sending to gui"
        echo $line >&${gui_in};
        if ! kill -0 $pid_gui;
        then
          gui_playing=0
          #break
        fi
      else
        :
      fi
    fi
  done
  if [ $ai_playing == 0 ];
  then
    wait $pid_ai
    ai_code=$?
    if (( $ai_code > 2 ));
    then
      #"Ai wywalilo blad"
      wait $pid_gui
      exit 1
    else
      #"Ai poprawnie sie skonczylo"
      wait $pid_gui
      gui_code=$?
      if [ $gui_code == 0 ];
      then
        #"Gui tez poprawnie sie skonczylo"
        exit 0
      else
        #"Gui niepoprawnie sie skonczylo"
        exit 1
      fi
    fi
  fi
  if [ $gui_playing == 0 ];
  then
    wait $pid_gui
    gui_code=$?
    if [ $gui_code == 0 ];
    then
      #"Gui poprawnie sie skonczylo"
      if kill -0 $pid_ai;
      then
        wait $pid_ai
        ai_code=$?
        if (( $ai_code > 2 ));
        then
          #"Ai jednak wywalilo sie"
          exit 1
        else
          #"Ai tez poprawnie sie skonczylo"
          exit 0
        fi
      fi
    else
      if kill -0 $pid_ai;
      then
        kill $pid_ai
      fi
      #"Gui wywalilo sie"
      exit 1
    fi
  fi
else
  #Uruchomienie gui dla dwoch ai
  ./$gui <&${gui_in} >&${gui_out} &
  pid_gui=$!
  #Uruchomienie obu ai
  $ai1 <&${ai1_in} >&${ai1_out} &
  pid_ai1=$!
  $ai2 <&${ai2_in} >&${ai2_out} &
  pid_ai2=$!
  #Inicjalizacja ai
  echo $init1 >&${ai1_in};
  echo $init2 >&${ai2_in};
  #Inicjalizacja gui
  echo $init1 >&${gui_in};
  echo $init2 >&${gui_in};
  gui_playing=1
  ai1_playing=1
  ai2_playing=1
  turn=1
  while [ "$gui_playing" -eq 1 ] && [ "$ai1_playing" -eq 1 -o "$ai2_playing" -eq 1 ];
  do
    if ! kill -0 $pid_ai1; then
      ai1_playing=0
      #break
    fi
    if ! kill -0 $pid_ai2; then
      ai2_playing=0
      #break
    fi
    if ! kill -0 $pid_gui; then
      gui_playing=0
      #break
    fi
    if [ "$turn" -eq 1 ];
    then
      #"player 1"
      read -t 0.4 line <&${ai1_out}
      if ! kill -0 $pid_ai1; then
        ai1_playing=0
        #break
      fi
      if [ "$line" == "" ];
      then
        :
      elif [[ "$line" =~ END_TURN ]];
      then
        #"end turn 1"
        #"sending to ai2"
        turn=2
        echo $line >&${ai2_in}
        if ! kill -0 $pid_ai2; then
          ai2_playing=0
          #break
        fi
        #"sending to gui"
        echo $line >&${gui_in}
        if ! kill -0 $pid_gui; then
          gui_playing=0
          #break
        fi
        sleep $waiting_time
      else
        #"sending to ai2"
        echo $line >&${ai2_in}
        if ! kill -0 $pid_ai2; then
          ai2_playing=0
          #break
        fi
        #"sending to gui"
        echo $line >&${gui_in}
        if ! kill -0 $pid_gui; then
          gui_playing=0
          #break
        fi
      fi
    else
      #"player 2"
      read -t 0.4 line <&${ai2_out}
      if ! kill -0 $pid_ai2; then
        ai2_playing=0
        #break
      fi
      if [[ "$line" =~ END_TURN ]];
      then
        #"end turn 2"
        turn=1
        #"sending to ai1"
        echo $line >&${ai1_in}
        if ! kill -0 $pid_ai1; then
          ai1_playing=0
          #break
        fi
        #"sending to gui"
        echo $line >&${gui_in}
        if ! kill -0 $pid_gui; then
          gui_playing=0
          #break
        fi
        sleep $waiting_time
      elif [ "$line" != ""  ];
      then
        #"sending to ai1"
        echo $line >&${ai1_in}
        if ! kill -0 $pid_ai1; then
          ai1_playing=0
          #break
        fi
        #"sending to gui"
        echo $line >&${gui_in}
        if ! kill -0 $pid_gui; then
          gui_playing=0
          #break
        fi
      else
        :
      fi
    fi
  done
  if [ $ai1_playing == 0 ];
  then
    wait $pid_ai1
    ai1_code=$?
    if (( $ai1_code > 2 ));
    then
      #"Ai1 wywalilo blad"
      if kill -0 $pid_ai2;
      then
        kill $pid_ai2
      fi
      wait $pid_gui
      exit 1
    else
      #"Ai1 poprawnie sie skonczylo"
      if kill -0 $pid_ai2;
      then
        #"Ale ai2 nie skonczylo sie"
        kill $pid_ai2
        wait $pid_gui
        exit 1
      fi
      #"Ai2 też skonczylo sie"
      wait $pid_gui
      gui_code=$?
      if [ $gui_code == 0 ];
      then
        #"Gui tez poprawnie sie skonczylo"
        exit 0
      else
        #"Gui niepoprawnie sie skonczylo"
        exit 1
      fi
    fi
  fi
  if [ $ai2_playing == 0 ];
  then
    wait $pid_ai2
    ai2_code=$?
    if (( $ai2_code > 2 ));
    then
      #"Ai2 wywalilo blad"
      if kill -0 $pid_ai1;
      then
        kill $pid_ai1
      fi
      wait $pid_gui
      exit 1
    else
      #"Ai2 poprawnie sie skonczylo"
      if kill -0 $pid_ai1;
      then
        #"Ale ai1 nie skonczylo sie"
        kill $pid_ai1
        wait $pid_gui
        exit 1
      fi
      #"Ai1 sie skonczylo jednak"
      wait $pid_gui
      gui_code=$?
      if [ $gui_code == 0 ];
      then
        #"Gui tez poprawnie sie skonczylo"
        exit 0
      else
        #"Gui niepoprawnie sie skonczylo"
        exit 1
      fi
    fi
  fi
  if [ $gui_playing == 0 ];
  then
    wait $pid_gui
    gui_code=$?
    if [ $gui_code == 0 ];
    then
      #"Gui poprawnie sie skonczylo"
      if kill -0 pid_ai1;
      then
        wait $pid_ai1
        ai1_code=$?
        if (( $ai1_code > 2 ));
        then
          :
          #"Ai1 tez poprawnie sie skonczylo"
        else
          #"Ai1 jednak wywalilo sie"
          exit 1
        fi
        wait $pid_ai2
        ai2_code=$?
        if (( $ai1_code > 2 ));
        then
          :
          #"Ai2 tez poprawnie sie skonczylo"
        else
          #"Ai2 jednak wywalilo sie"
          exit 1
        fi
        exit 0
      fi
    else
      if kill -0 $pid_ai1;
      then
        kill $pid_ai1
      fi
      if kill -0 $pid_ai2;
      then
        kill $pid_ai2
      fi
      #"Gui wywalilo sie"
      exit 1
    fi
  fi
fi
#"Nie powinienes tu byc! Chyba..."
#exit 0;
