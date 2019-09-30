:- module(getting_started, []).
:- use_module(library(filesex)).

:- initialization example.

example :-
    % uncomment next line to follow execution step by step
    % trace,

    module_property(getting_started,file(ModuleFile)),
    file_directory_name(ModuleFile,ModuleDir),
    directory_file_path(ModuleDir, 'img/milla.bmp', Milla),
    
    cImg:new(Milla,Image),
    cImg:new(500,400,1,3,0,Visu),

    cImg:blur(Image,2.5),

    cImgDisplay:new(Image,"Click a point",Main_disp),
    cImgDisplay:new(Visu,"Intensity profile",Draw_disp),

    loop(Image,Visu,Main_disp,Draw_disp).

loop(_,_,Main_disp,Draw_disp) :-
    ( cImgDisplay:is_closed(Main_disp) ; cImgDisplay:is_closed(Draw_disp) ), !.

loop(Image,Visu,Main_disp,Draw_disp) :-
    cImgDisplay:wait(Main_disp),
    (   cImgDisplay:button(Main_disp,1)
    ->  cImgDisplay:mouse_y(Main_disp,Y),
        (   Y >= 0
        ->  cImg:width(Image,W), W1 is W-1,
            Red = [ 255,0,0 ], Green = [ 0,255,0 ], Blue = [ 0,0,255 ],
            cImg:get_crop(Image,[0,Y,0,0,W1,Y,0,0],CropR),
            cImg:get_crop(Image,[0,Y,0,1,W1,Y,0,1],CropG),
            cImg:get_crop(Image,[0,Y,0,2,W1,Y,0,2],CropB),

            cImg:fill(Visu,0),
            cImg:draw_graph(Visu,CropR,Red,1,1,0,255,0),
            cImg:draw_graph(Visu,CropG,Green,1,1,0,255,0),
            cImg:draw_graph(Visu,CropB,Blue,1,1,0,255,0),
            cImg:display(Visu,Draw_disp),

            cImg:delete(CropR),
            cImg:delete(CropG),
            cImg:delete(CropB)

        ;   true
        )
    ;   true
    ),
    !, loop(Image,Visu,Main_disp,Draw_disp).
