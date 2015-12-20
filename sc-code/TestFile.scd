// THIS FILE IS FOR TESTING SC CODE IT MAYBE FILLED WITH GARBAGE


Ndef(\envFollow,Fdef(\env_follower));
Ndef(\whiteNoise, Fdef(\whiteNoise));
Ndef('whiteNoise')<>>Ndef('envFollow');
(
Tdef(\getEnvellope, {
	loop{
		Ndef('envFollow').bus.subBus(0,1).get({
			|v|
			v.postln;
		});
		1.wait;
	}
}
).play
)

Ndef('whiteNoise').set('amp', 1)

b.stop
0.postln
