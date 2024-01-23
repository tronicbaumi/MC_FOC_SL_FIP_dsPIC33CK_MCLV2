//function  y = qei_sim2(u1)
//    in = u1;
//    out = u1;
//    
//    out = modulo(in, 2*%pi/5);
//    out = out * (500/%pi);
//    
//    y = out;
//endfunction


function  y = qei_sim2(u1)
    in = u1*5+%pi;
    out = u1;
    if in > %pi then
        out =  modulo(in-%pi, 2*%pi) - %pi;
    end
    if in < -%pi then
        out =  modulo(in+%pi, 2*%pi) + %pi;
    end

    y = out*1/%pi;
endfunction
