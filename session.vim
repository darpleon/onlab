let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/tan/onlab/project
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +30 src/main.cpp
badd +109 src/Context.cpp
badd +15 src/Context.hpp
badd +168 ~/tan/onlab/project/src/Graphics.cpp
badd +77 src/Graphics.hpp
badd +1 src/Shader.hpp
badd +7 src/shader/basic.vert
badd +94 src/Polynomial.hpp
badd +39 src/Bernstein.hpp
badd +85 ../tema-spline-main/src/Graphics.cpp
badd +11 CMakeLists.txt
badd +14 src/PHPlanarQuintic.hpp
badd +67 src/PHPlanarQuintic.cpp
badd +28 src/Listener.hpp
badd +24 src/PHDemo.hpp
badd +41 src/PHDemo.cpp
argglobal
%argdel
$argadd src/main.cpp
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/PHDemo.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 27 + 31) / 62)
exe 'vert 1resize ' . ((&columns * 106 + 136) / 273)
exe '2resize ' . ((&lines * 31 + 31) / 62)
exe 'vert 2resize ' . ((&columns * 106 + 136) / 273)
exe 'vert 3resize ' . ((&columns * 166 + 136) / 273)
argglobal
balt src/PHDemo.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 27 - ((5 * winheight(0) + 13) / 27)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/PHDemo.hpp", ":p")) | buffer src/PHDemo.hpp | else | edit src/PHDemo.hpp | endif
if &buftype ==# 'terminal'
  silent file src/PHDemo.hpp
endif
balt src/PHDemo.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 14 - ((12 * winheight(0) + 15) / 31)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/Listener.hpp", ":p")) | buffer src/Listener.hpp | else | edit src/Listener.hpp | endif
if &buftype ==# 'terminal'
  silent file src/Listener.hpp
endif
balt src/PHDemo.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 20 - ((19 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 20
normal! 017|
wincmd w
exe '1resize ' . ((&lines * 27 + 31) / 62)
exe 'vert 1resize ' . ((&columns * 106 + 136) / 273)
exe '2resize ' . ((&lines * 31 + 31) / 62)
exe 'vert 2resize ' . ((&columns * 106 + 136) / 273)
exe 'vert 3resize ' . ((&columns * 166 + 136) / 273)
tabnext
edit src/Context.hpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 106 + 136) / 273)
exe 'vert 2resize ' . ((&columns * 166 + 136) / 273)
argglobal
balt src/Context.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 16 - ((15 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/Context.cpp", ":p")) | buffer src/Context.cpp | else | edit src/Context.cpp | endif
if &buftype ==# 'terminal'
  silent file src/Context.cpp
endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 107 - ((25 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 107
normal! 011|
wincmd w
exe 'vert 1resize ' . ((&columns * 106 + 136) / 273)
exe 'vert 2resize ' . ((&columns * 166 + 136) / 273)
tabnext
edit src/Graphics.hpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 28 + 31) / 62)
exe 'vert 1resize ' . ((&columns * 124 + 136) / 273)
exe '2resize ' . ((&lines * 30 + 31) / 62)
exe 'vert 2resize ' . ((&columns * 124 + 136) / 273)
exe 'vert 3resize ' . ((&columns * 148 + 136) / 273)
argglobal
balt ~/tan/onlab/project/src/Graphics.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 77 - ((16 * winheight(0) + 14) / 28)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 77
normal! 031|
wincmd w
argglobal
if bufexists(fnamemodify("~/tan/onlab/project/src/Graphics.cpp", ":p")) | buffer ~/tan/onlab/project/src/Graphics.cpp | else | edit ~/tan/onlab/project/src/Graphics.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/tan/onlab/project/src/Graphics.cpp
endif
balt src/Graphics.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 168 - ((21 * winheight(0) + 15) / 30)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 168
normal! 020|
wincmd w
argglobal
if bufexists(fnamemodify("src/main.cpp", ":p")) | buffer src/main.cpp | else | edit src/main.cpp | endif
if &buftype ==# 'terminal'
  silent file src/main.cpp
endif
balt ~/tan/onlab/project/src/Graphics.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 25 - ((18 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 25
normal! 015|
wincmd w
exe '1resize ' . ((&lines * 28 + 31) / 62)
exe 'vert 1resize ' . ((&columns * 124 + 136) / 273)
exe '2resize ' . ((&lines * 30 + 31) / 62)
exe 'vert 2resize ' . ((&columns * 124 + 136) / 273)
exe 'vert 3resize ' . ((&columns * 148 + 136) / 273)
tabnext
edit src/PHPlanarQuintic.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 136 + 136) / 273)
exe 'vert 2resize ' . ((&columns * 136 + 136) / 273)
argglobal
balt src/PHPlanarQuintic.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 43 - ((30 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 43
normal! 025|
wincmd w
argglobal
if bufexists(fnamemodify("src/PHPlanarQuintic.hpp", ":p")) | buffer src/PHPlanarQuintic.hpp | else | edit src/PHPlanarQuintic.hpp | endif
if &buftype ==# 'terminal'
  silent file src/PHPlanarQuintic.hpp
endif
balt src/PHPlanarQuintic.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 27 - ((26 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 021|
wincmd w
exe 'vert 1resize ' . ((&columns * 136 + 136) / 273)
exe 'vert 2resize ' . ((&columns * 136 + 136) / 273)
tabnext
edit src/Bernstein.hpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 135 + 136) / 273)
exe 'vert 2resize ' . ((&columns * 137 + 136) / 273)
argglobal
balt src/Polynomial.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 66 - ((53 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 66
normal! 036|
wincmd w
argglobal
if bufexists(fnamemodify("src/Polynomial.hpp", ":p")) | buffer src/Polynomial.hpp | else | edit src/Polynomial.hpp | endif
if &buftype ==# 'terminal'
  silent file src/Polynomial.hpp
endif
balt src/Bernstein.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 54 - ((53 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 54
normal! 03|
wincmd w
exe 'vert 1resize ' . ((&columns * 135 + 136) / 273)
exe 'vert 2resize ' . ((&columns * 137 + 136) / 273)
tabnext 4
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
