// THIS FILE IS FOR TESTING SC CODE IT MAYBE FILLED WITH GARBAGE
Environment.stack
currentEnvironment 
currentEnvironment === topEnvironment

topEnvironment

~etudes = (
    midiMap: {
        arg synth, parameter,  midiCC, minVal, maxVal;
        Ndef(synth.asSymbol).map(parameter.asSymbol, 
            Ndef((synth.asSymbol ++ parameter.asSymbol ++ midiCC.asSymbol),
                {~midiBus[midiCC].kr(1).linlin(0,1,minVal,maxVal)}
        ));
    } 
)


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
