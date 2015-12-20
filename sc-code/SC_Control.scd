//s.options.device = "Saffire";
(
    Tdef(\init, {
        // @todo working directory or a SC_CODE_DIR environment
        // variable
        ~myPath = "/Users/claudiocabral/Projetos/etudes/sc-code/";

        (~myPath ++ "Server.scd").load;

        s.bootSync;

        (~myPath ++ "Midi.scd").load;
        s.sync;
        (~myPath ++ "Definitions.scd").load;
        s.sync;

        Tdef(\oscUpdate, {
            loop{
                ~midiBus[116].get({ arg v; ~patric.sendMsg("/lines/distance/amplitude", v.linlin(0,1,0,0.02)); });
                ~midiBus[27].get({ arg v; ~patric.sendMsg("/lines/angle",v); });
                0.016.wait;
            }
        });

        s.sync;

        //NDEFS
        Ndef('sinOsc1', Fdef(\sinOsc)).set('freq', 300, 'mul', 300,'add', 35);
        s.sync;
        Ndef('sinOsc2', Fdef(\sinOsc)).set('freq', 300, 'mul', 0.5,'add', 0.5);
        s.sync;
        Ndef('sinOsc3', Fdef(\sinOsc)).set('freq', 300, 'mul', 0.5,'add', 0.5);
        s.sync;
        Ndef('lfSaw1', Fdef(\lfSaw)).set('freq', 1, 'mul', 100,'add', 1);
        s.sync;
        Ndef('lfPulse1', Fdef(\lfPulse)).set('freq', 300, 'mul', 50,'add', 100);
        s.sync;
        Ndef('noise', Fdef(\noise)).set('freq', 300, 'mul', 2,'add', -1);
        s.sync;

        // NDEF ROUTING
        Ndef('sinOsc2').map(\freq, Ndef('sinOsc1'));
        s.sync;
        Ndef('sinOsc3').map(\freq, Ndef('lfsaw'));
        s.sync;
        Ndef('lfPulse1').map(\width, Ndef('sinOsc3'));
        s.sync;
        Ndef('noise').map(\width, Ndef('sinOsc2'));
        s.sync;
        Ndef('noise').map(\freq,Ndef('lfPulse1'));
        s.sync;

        // MIDI MAP
        Ndef(\lfPulse1).map(\add, Ndef('mapper',{~midiBus[116].kr(1) * 300}));
        s.sync;
        Ndef(\lfPulse1).map(\freq, Ndef('mapper2',{~midiBus[27].kr(1) * 300}));
        s.sync;

        "done".postln;
    });
    Tdef(\init).play;
)

// CONTROL AREA
Tdef(\oscUpdate).play(doReset:true)
Tdef(\oscUpdate).stop

Ndef(\noise).play(0,2)
Ndef(\noise).stop

s.quit
