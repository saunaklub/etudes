~env_follower = {
    var sig, outArray;
    var low, mid, high;

    sig = \in.ar(0);

    low  = LPF.ar(sig, \low_freq.kr(100));
    mid  = BPF.ar(sig, \mid_freq.kr(1000), \rq.kr(2));
    high = HPF.ar(sig, \high_freq.kr(5000));

    low  = PeakFollower.kr(low);
    mid  = PeakFollower.kr(mid);
    high = PeakFollower.kr(high);

    outArray = [low, mid, high];
}

Ndef(\envFollow, ~env_follower);
