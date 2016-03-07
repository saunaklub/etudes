Environment.push(~etudes);

~midiMap = {
    arg synth, parameter,  midiCC, minVal, maxVal;
    Ndef(synth.asSymbol).map(parameter.asSymbol, 
        Ndef((synth.asSymbol ++ parameter.asSymbol ++ midiCC.asSymbol),
        {~midi.bus[midiCC].kr(1).linlin(0,1,minVal,maxVal)}
    ));
};

~valueRegister = IdentityDictionary();

~registerValue = {
    arg oscpath, synth, inputMin, inputMax, outputMin, outputMax;
    ~valueRegister.put(
        oscpath.asSymbol,
        [oscpath.asString, synth.asSymbol, inputMin, inputMax, outputMin, outputMax]
    );
};

~sendValues = {
    ~valueRegister.do{
        arg item, i;
        Ndef(item[1]).bus.get({
            arg v;
            ~server.sendMsg(
                item[0], v.linlin(item[2], item[3], item[4], item[5]);
            )
        })
    };
};

Environment.pop;
