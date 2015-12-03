/*
instructions:place cursor in line s.waitForBoot and
evaluate everthing in between parenthesis with ctrl (command on mac)  RET

on line 66 evaluate lines as needed to stop and start osc and noise output
I'm using midi CC 116 and 27, but on supercollider midi goes from 0 to 127
so it's possible that elsewhere this means CCs 117 and 28. Try and see
*/
// use this option to change the audio device if need. 
// When set to nil uses your computers default device 
// s.options.device = "Saffire"
(
s.waitForBoot({
// change the string to IP if needed and integer to port
~patric =  NetAddr.new("localhost", 6666);

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

// SEND OSC ROUTINE
~oscUpdate = Task({
	loop{
		~midiBus[116].get({arg v;~patric.sendMsg("/lines/distance/amplitude",v.linlin(0,1,0,0.02));});
		~midiBus[27].get({arg v;~patric.sendMsg("/lines/distance/frequency",v);});
		0.016.wait;
	}
});

~noise ={

	var sig, env, lfpulse, lfsaw, sinosc1, sinosc2, sinosc3;

	sinosc1 = SinOsc.ar(300,0,\sinOsc1Mul.ar(300),\sinOsc1Add.ar(35));

	sinosc2 = SinOsc.ar(sinosc1,mul:0.5,add:0.5);

	lfsaw = LFSaw.ar(\sawFreq.ar(1),0,\sawMul.ar(100),1);

	sinosc3 = SinOsc.ar(lfsaw,mul:0.5,add:0.5);

	lfpulse = LFPulse.ar(\baseModFreq.ar(100), width:sinosc3,mul:\modWidthFreq.ar(50));

	sig = LFPulse.ar(\baseFreq.ar(75) + lfpulse, width:sinosc2,mul:2,add:-1) * \amp.ar(0.05);

	env = EnvGen.ar(Env.adsr(0.01,0,1,0.1));

	sig * env;
};

Ndef(\noise, ~noise);
// Change and evaluate the numbers in brackets  with shift + RET in these lines
// to change the midi CC
Ndef(\noise).map(\baseFreq, Ndef('mapper',{~midiBus[116].kr(1) * 300}));
Ndef(\noise).map(\baseModFreq, Ndef('mapper2',{~midiBus[27].ar(1) * 300}));
});
)
// START AND STOP NOISE AND SENDING OSC
Ndef(\noise).play(0,2)
Ndef(\noise).stop
~oscUpdate.play(doReset:true)
~oscUpdate.stop 
