set terminal cairolatex eps mono transparent size 5.00in, 2.40in

title = ''
output = ''
if(ARG1 eq 'time'){
  title = 'Time performance for '
  output = 'time-'
  set ylabel "time (s)"
} else {
  title = 'Space performance for '
  output = 'space-'
  set ylabel "space (Mb)"
}

if(ARG2 eq 'Fm'){
  title = title . 'Fixed $m = 0$'
  output = output . 'Fm'
  set xlabel "$n$"
} else {
  title = title . 'Fixed $n = 1$'
  output = output . 'Fn'
  set xlabel "$m$"
}

output = output . '.tex'
set output output
set key bottom right

if(ARG1 eq 'time'){

  if(ARG2 eq 'Fm'){
    set logscale y
    set yrange [:]
    plot \
      "Floyd-Fixed-m.dat" u 3:($4/$1) with linespoints title "Floyd" pt 2, \
      "Galois-Fixed-m.dat" u 3:($4/$1) with linespoints title "Galois" pt 6
  } else {
    set yrange [0:]
    plot \
      "Floyd-Fixed-n.dat" u 3:($4/$1) with linespoints title "Floyd" pt 2, \
      "Galois-Fixed-n.dat" u 3:($4/$1) with linespoints title "Galois" pt 6
  }
} else {
  set yrange [0:]
  if(ARG2 eq 'Fm'){
    plot \
      "Floyd-Fixed-m.dat" u 3:($5/1024) with linespoints title "Floyd" pt 2, \
      "Galois-Fixed-m.dat" u 3:($5/1024) with linespoints title "Galois" pt 6
  } else {
    plot \
      "Floyd-Fixed-n.dat" u 3:($5/1024) with linespoints title "Floyd" pt 2, \
      "Galois-Fixed-n.dat" u 3:($5/1024) with linespoints title "Galois" pt 6
  }
}
