(
s.waitForBoot({
~etudes =  NetAddr.new("localhost", 6666);

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
	~midiBus[cc].set(val/2048);
});

~oscUpdate = Task({
	loop{
		~midiBus[116].get({
				arg v;
				~etudes.sendMsg("/lines/distance/amplitude", v);
			});
		~midiBus[27].get({
				arg v;
				~etudes.sendMsg("/lines/distance/omega", v);
			});
		~etudes.sendMsg("/lines/distance/base", 10);

		0.016.wait;
	}
});

~noise ={
	var sig, env, lfpulse, lfsaw, sinosc1, sinosc2, sinosc3;

	sinosc1 = SinOsc.ar(
			300, 0,
			\sinOsc1Mul.ar(300),
			\sinOsc1Add.ar(35)
		);
	sinosc2 = SinOsc.ar(
			sinosc1,
			mul:0.5,
			add:0.5
		);

	lfsaw = LFSaw.ar(
			\sawFreq.ar(1), 0,
			\sawMul.ar(100),1
		);

	sinosc3 = SinOsc.ar(
			lfsaw,mul:0.5,
			add:0.5
		);

	lfpulse = LFPulse.ar(
			\baseModFreq.ar(100),
			width:sinosc3,
			mul:\modWidthFreq.ar(50)
		);

	sig = LFPulse.ar(
			\baseFreq.ar(75) + lfpulse,
			width:sinosc2,
			mul:2,
			add:-1)
		* \amp.ar(0.05);

	env = EnvGen.ar(Env.adsr(0.01, 0, 1, 0.1));

	sig * env;
};

Ndef(\noise, ~noise);
Ndef(\noise).map(\baseFreq, Ndef('mapper', {~midiBus[116].kr(1) * 300} ));
Ndef(\noise).map(\baseModFreq, Ndef('mapper2', {~midiBus[27].ar(1) * 300} ));
});
)

Ndef(\noise).play(0, 2)
Ndef(\noise).stop
~oscUpdate.play(doReset:true)
~oscUpdate.stop
