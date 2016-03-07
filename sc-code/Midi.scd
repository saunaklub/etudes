MIDIClient.init;
MIDIIn.connectAll;

Environment.push(~etudes);
~midi = ();
Environment.push(~midi);

if (~bus == nil) {~bus = Array.newClear(128)};
128.do{
    arg i;
    if(~bus[i] == nil) {~bus[i]= Bus.control(s,1)}
};


MIDIdef.cc(\midiCC,{
    arg val, cc, chan;
    [val/127,cc,chan].postln;
    ~bus[cc].set(val/127);
});

Environment.pop; //midi
Environment.pop; //etudes
