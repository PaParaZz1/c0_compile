set nocompatible              " 这是必需的 
filetype off                  " 这是必需的 

" 你在此设置运行时路径 
set rtp+=~/.vim/bundle/vundle  

" vundle初始化 
call vundle#begin()  

" 这应该始终是第一个 
Plugin 'gmarik/Vundle.vim' 

" 该例子来自https://github.com/gmarik/Vundle.vim README 
Plugin 'tpope/vim-fugitive'  

" 来自http://vim-scripts.org/vim/scripts.html的插件 
Plugin 'L9'  

"未托管在GitHub上的Git插件 
Plugin 'git://git.wincent.com/command-t.git'  


" sparkup vim脚本在名为vim的该软件库子目录下。 
" 传递路径，合理设置运行时路径。 
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'} 

Bundle 'SuperTab'
" ###### 主题 molokai 和 Solarized                                                                                                           
Bundle 'tomasr/molokai'                                                                                                                      
let g:molokai_original = 1                                                                                                                   
Bundle 'altercation/vim-colors-solarized'                                                                                                    
let g:solarized_termcolors=256                                                                                                               
let g:solarized_termtrans=1                                                                                                                  
let g:solarized_contrast="normal"                                                                                                            
let g:solarized_visibility="normal"                                                                                                          
" 主题使用                                                                                                                                   
set background=dark                                                                                                                          
"set background=light                                                                                                                        
set t_Co=256                                                                                                                                 
"colorscheme molokai                                                                                                                          
"colorscheme solarized

" ###### 多语言语法检查                                                                                                                      
Bundle 'scrooloose/syntastic'                                                                                                    
set statusline+=%#warningmsg#                                                                                                                
set statusline+=%{SyntasticStatuslineFlag()}                                                                                                 
set statusline+=%*           
    " 检测到错误和警告时的标志                                                                                                                
let g:syntastic_error_symbol='✘✘'                                                                                                            
let g:syntastic_warning_symbol='➤➤'                                                                                                          
let g:syntastic_check_on_open=1                                                                                                              
let g:syntastic_check_on_wq=0                                                                                                                
let g:syntastic_enable_highlighting=1                                                                                                        
    " 使用pyflakes,速度比pylint快
    " 需要安装 pep8 或者 pyflakes，使用pip安装  ,pep8是python的格式检测神器，建议安装。                                                                                       
let g:syntastic_python_checkers=['pep8', 'pyflakes']                                                                                         
let g:syntastic_cpp_cpplint_exec="cpplint"
let g:syntastic_cpp_checkers=['cpplint']                                                                                         
let g:syntastic_python_pep8_args='--ignore=E501,E225'                                                                                        
    " 修改高亮的背景色, 适应主题                                                                                                             
highlight SyntasticErrorSign guifg=white guibg=black                                                                                         
" to see error location list                                                                                                                 
let g:syntastic_always_populate_loc_list = 0                                                                                                 
let g:syntastic_auto_loc_list = 0                                                                                                            
let g:syntastic_loc_list_height = 5                                                                                                          
function! ToggleErrors()                                                                                                                     
    let old_last_winnr = winnr('$')                                                                                                          
    lclose                                                                                                                                   
    if old_last_winnr == winnr('$')                                                                                                          
        " Nothing was closed, open syntastic error location panel                                                                            
        Errors                                                                                                                               
    endif                                                                                                                                    
endfunction                                                                                                                                  
nnoremap <Leader>s :call ToggleErrors()<cr>      
    " 跳转到下一个/上一个错误处                                                                                            
nnoremap <Leader>sn :lnext<cr>                                                                                                               
nnoremap <Leader>sp :lprevious<cr>
    " 关闭 某一语言的（如C/C++） 的语法检测                                                                        
" let g:syntastic_ignore_files=[".*\.c$", ".*\.h$", ".*\.cpp", ".*\.hpp"]

"每个插件都应该在这一行之前  

call vundle#end()          
set nu 
syntax on
set ts=4
set mouse+=a
set expandtab
set shiftwidth=4
set autoindent
