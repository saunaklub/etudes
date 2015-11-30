//FUNCS
(
	~main = Task({
		~sinOsc = {
			SinOsc.kr(\freq.kr(440),0,\mul.kr(1),\add.kr(0));
		};

		~lfSaw = {
			LFSaw.kr(\freq.kr(440),0,\mul.kr(300),\add.kr(0));
		};

		~lfPulse = {
			LFPulse.kr(\freq.kr(440),\width.kr(0.5),\mul.kr(1),\add.kr(0));
		};

		~noise2 = {LFPulse.ar(\freq.ar(300),\width.ar(0.5),\mul.ar(1)) * \amp.ar(0.05)};

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

		~mapFunc = {arg in,min,max;LinLin.kr(in,0,1,min,max);};

		//NDEFS
		Ndef('sinOsc1', ~sinOsc).set('freq', 300, 'mul', 300,'add', 35);
		0.5.wait;
		Ndef('sinOsc2', ~sinOsc).set('freq', 300, 'mul', 0.5,'add', 0.5);
		0.5.wait;
		Ndef('sinOsc3', ~sinOsc).set('freq', 300, 'mul', 0.5,'add', 0.5);
		0.5.wait;
		Ndef('lfSaw1', ~lfSaw).set('freq', 1, 'mul', 100,'add', 1);
		0.5.wait;
		Ndef('lfPulse1', ~lfPulse).set('freq', 100, 'mul', 50,'add', 0);
		0.5.wait;
		Ndef('noise2', ~noise2).set('freq', 300, 'mul', 1,'add', 0);
		0.5.wait;
		// NDEF ROUTING


		Ndef('sinosc1') <>>.freq Ndef('sinosc2');
		Ndef('lfsaw') <>>.freq Ndef('sinosc3');
		Ndef('sinosc3') <>>.width Ndef('lfPulse1'); 
		Ndef('sinosc2') <>>.width Ndef('noise2');

		Ndef('lfPulse1') <>>.freq Ndef('noise2');
	}).play;
)

Ndef('noise2').play(0,2)
Ndef('noise2').stop
