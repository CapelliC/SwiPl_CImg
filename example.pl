
:- initialization example.

example :-
    % trace, uncomment to follow execution step by step

    cImg("/home/carlo/test/CImg/examples/img/milla.bmp",Image),
    cImg(500,400,1,3,0,Visu),

    blur(Image,2.5),

    cImgDisplay(Image,"Click a point",Main_disp),
    cImgDisplay(Visu,"Intensity profile",Draw_disp),

    loop(Image,Visu,Main_disp,Draw_disp).

loop(_,_,Main_disp,Draw_disp) :-
    ( is_closed(Main_disp) ; is_closed(Draw_disp) ), !.

loop(Image,Visu,Main_disp,Draw_disp) :-
    wait(Main_disp),
    (   button(Main_disp,1)
    ->  mouse_y(Main_disp,Y),
        (   Y >= 0
        ->  width(Image,W), W1 is W-1,
            Red = [ 255,0,0 ], Green = [ 0,255,0 ], Blue = [ 0,0,255 ],
            get_crop(Image,[0,Y,0,0,W1,Y,0,0],CropR),
            get_crop(Image,[0,Y,0,1,W1,Y,0,1],CropG),
            get_crop(Image,[0,Y,0,2,W1,Y,0,2],CropB),

            fill(Visu,0),
            draw_graph(Visu,CropR,Red,1,1,0,255,0),
            draw_graph(Visu,CropG,Green,1,1,0,255,0),
            draw_graph(Visu,CropB,Blue,1,1,0,255,0),
            display(Visu,Draw_disp),

            cImg_free(CropR),
            cImg_free(CropG),
            cImg_free(CropB)

        ;   true
        )
    ;   true
    ),
    !, loop(Image,Visu,Main_disp,Draw_disp).
