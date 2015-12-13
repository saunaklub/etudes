~sinOsc = {
	SinOsc.ar(\freq.ar(440),0,\mul.ar(1),\add.ar(0));
};

~lfSaw = {
	LFSaw.ar(\freq.ar(440),0,\mul.ar(300),\add.ar(0));
};

~lfPulse = {LFPulse.ar(\freq.ar(439), 0, \width.ar(0.5),\mul.ar(0.05),\add.ar(0))};

~noise = {LFPulse.ar(\freq.ar(300), 0, \width.ar(0.5),\mul.ar(0.05))};

~input = {SoundIn.ar(\bus.kr(0))};

~env_follower = {
	var sig, outArray, low, high,mid;
	sig = \in.ar(0);
	low = LPF.ar(sig,\low_freq.kr(100));
	mid = BPF.ar(sig,\mid_freq.kr(1000),\rq.kr(2));
	high = HPF.ar(sig,\high_freq.kr(5000));
	low = PeakFollower.kr(low);
	mid = PeakFollower.kr(mid);
	high = PeakFollower.kr(high);
	outArray = [low, mid, high];
    outArray;
};

~noiseRef ={

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

~converter = {A2K.kr(\in.ar(0))};

~whiteNoise = {WhiteNoise.ar(\amp.ar(1))};

~mapFunc = {arg in,min,max;LinLin.kr(in,0,1,min,max);};
