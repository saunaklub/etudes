(
	~init = Task({
		~myPath = "/Users/claudiocabral/Projetos/etudes/osc/";
		1.wait;
		(~myPath ++"Server.scd").load;
		1.wait;
		s.waitForBoot(
			(~myPath ++ "Midi.scd").load;
			s.wait;
			(~myPath ++"Definitions.scd").load; 
			s.wait;
			~oscUpdate = Task({

					//	Ndef('converter').bus.get({arg v; v.postln;});
					~midiBus[116].get({arg v;~patric.sendMsg("/lines/distance/base",v.linlin(0,1,0,0.02));});
					~midiBus[27].get({arg v;~patric.sendMsg("/lines/angle",v);});
					0.016.wait;
				});
			s.wait;
		);
	}
);
~init.play;
)
s.options.device = "Saffire";
s.quit

Ndef(\noise).play(0,2)
Ndef(\noise).stop

// MIDI MAP
Ndef(\lfPulse1).map(\add, Ndef('mapper',{~midiBus[116].kr(1) * 300}))
Ndef(\lfPulse1).map(\freq, Ndef('mapper2',{~midiBus[27].ar(1) * 300}))

~oscUpdate.stop 
~oscUpdate.play(doReset:true)

Ndef('converter', ~converter);
// SEND OSC ROUTINE
(
)

//NDEFS
Ndef('sinOsc1', ~sinOsc).set('freq', 300, 'mul', 300,'add', 35);
Ndef('sinOsc2', ~sinOsc).set('freq', 300, 'mul', 0.5,'add', 0.5);
Ndef('sinOsc3', ~sinOsc).set('freq', 300, 'mul', 0.5,'add', 0.5);
Ndef('lfSaw1', ~lfSaw).set('freq', 1, 'mul', 100,'add', 1);
Ndef('lfPulse1', ~lfPulse).set('freq', 300, 'mul', 50,'add', 100);
Ndef('noise', ~noise).set('freq', 300, 'mul', 2,'add', -1);
// NDEF ROUTING

Ndef('sinOsc2').map(\freq, Ndef('sinOsc1'));
Ndef('sinOsc3').map(\freq, Ndef('lfsaw'));
Ndef('lfPulse1').map(\width, Ndef('sinOsc3')); 
Ndef('noise').map(\width, Ndef('sinOsc2'));
Ndef('noise').map(\freq,Ndef('lfPulse1'))
Ndef(\envFollow,~env_follower);
