//SYTH CREATION

Ndef(\noise, ~noise)
Ndef(\noise).play(0,2)
Ndef(\noise).stop
// MIDI MAP
Ndef(\noise, ~noise).set('amp', 0.1)

Ndef('noise').index
Ndef(\noise).map(\baseFreq, Ndef('mapper',{~midiBus[116].kr(1) * 300}))
s.plotTree
Ndef(\noise).map(\baseModFreq, Ndef('mapper2',{~midiBus[27].ar(1) * 300}))
Ndef(\noise).set(\baseFreq, 100)

~oscUpdate.stop 
~oscUpdate.play(doReset:true)

Ndef('converter', {A2K.kr(Ndef('noise'))});
// SEND OSC ROUTINE
(
~oscUpdate = Task({
	loop{
//	Ndef('converter').bus.get({arg v; v.postln;});
		~midiBus[116].get({arg v;~patric.sendMsg("/lines/distance/amplitude",v.linlin(0,1,0,0.02));});
		~midiBus[27].get({arg v;~patric.sendMsg("/lines/distance/frequency",v);});
		0.016.wait;
	}
});
)
