~localServer = Server.supernova.local
~localServer.boot
~localServer.quit
//NET ADDRESSES
~patric =  NetAddr.new("192.168.2.5", 6000);
~patric.sendMsg("/test",1.0);

// BUSSES
~lfoValue = Bus.control(~localServer,1);

// MIDI INIT
MIDIClient.init;
MIDIIn.connectAll;

// SYNTHS DEFS
(
SynthDef(\LFOSaw,{
arg controlBus,outputBus, freq,lfoFreq,gain;
	var sig = Saw.ar(freq,1.0);
	var lfo = SinOsc.kr(lfoFreq);

	sig = MoogFF.ar(sig, freq*2 + (freq * lfo),gain);
	Out.kr(controlBus,lfo);
	Out.ar(outputBus,sig!2);

}).add;
)

// MIDI DEFS

(
MIDIdef.cc(\quneoOneOne,{
arg val, cc, chan;
	if(cc == 1){
	[val,cc,chan].postln;
	~lfoSynth.set(\lfoFreq, val.linexp(0,127,0.01,500));
	}
},1,1).add;
)

MIDIdef.freeAll

//SYTH CREATION
~lfoSynth = Synth(\LFOSaw,[\controlBus,~lfoValue,\outputBus,0,\freq,220,\lfoFreq,0.1,\gain,2.0])
~lfoSynth.free;
~lfoSynth.set(\gain, 2.0)
~lfoSynth.set(\lfoFreq, 2.0)

~oscUpdate.stop

~oscUpdate.play(doReset:true)

// SEND OSC ROUTINE
(
~oscUpdate = Task({
	loop{
		~lfoValue.get({arg v;~patric.sendMsg("/test",v);});
		0.016.wait;
	}
});
)


~localServer.meter
~localServer.quit


