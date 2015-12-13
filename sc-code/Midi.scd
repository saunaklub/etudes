MIDIClient.init;
MIDIIn.connectAll;

if (~midiBus == nil) {~midiBus = Array.newClear(128)};
128.do{
	arg i;
	if(~midiBus[i] == nil) {~midiBus[i]= Bus.control(s,1)}
};


MIDIdef.cc(\midiCC,{
	arg val, cc, chan;
	[val/127,cc,chan].postln;
	~midiBus[cc].set(val/127);
});

//MIDIdef.noteOn(\noteIn, {
//	arg vel = 0, nn = 0;
//	// [nn,channel].postln;
//	// ~midiKeyboard[nn] =Synth(\FM, [\freq, nn.midicps]);
//});
//
//
//MIDIdef.noteOff(\noteIn, {
//	arg nn = 0, channel = 0;
//	//[nn,channel].postln;
//
//	~midiKeyboard[nn].set(\gate,0);
//	~midiKeyboard[nn] = nil;
//});


