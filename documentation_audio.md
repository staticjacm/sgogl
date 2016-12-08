# Loading and Unloading

To load a .wav file use

```c
int gr_load_wav(char* file, int id)
```

``file`` is the .wav file to load and id is the audio id to register the file under. If the id is in use then the audio currently using that id is unloaded and replaced with this one. If 0 is passed as the id then the function will find the first unused id and use that instead. The returned int is the actual id used, or -1 if there was an error.

You can easily unload an audio sample registered to an id by using

```c
void gr_unload_audio(int id)
```

# Play Controls

Play a given audio sample id with one of the following

```c
int gr_play_once(int id)
int gr_play_once_on(int id, int channel)
int gr_play(int id, int loops)
int gr_play_on(int id, int loops, int channel)
int gr_play_timed(int id, int time_ms)
int gr_play_timed_on(int id, int channel, int time_ms)
```

The ``channel`` parameter is mix channel to use. If channel is -1 then an unused channel is found to play on. The returned value for each of these is the actual channel the sample will play on. The channel of the played sample should be remembered if you want to change the volume, panning, attenuation or if you want to pause or stop the sample. If loops is -1 then the sample will loop forever (except in the case of ``gr_play_timed`` in which case it will stop after ``time_ms`` milliseconds), so it is probably a good idea to record the channel id if you want to set loops to -1.

Pausing a channel doesn't unregister the sample and can be resumed

```c
void gr_pause(int channel)
void gr_resume(int channel)
int gr_paused(int channel)
```

Stopping a channel unregisters the sample associated with it

```c
void gr_stop(int channel)
int gr_stopped(int channel)
```

# Effects

Set a channel's volume with

```c
void gr_set_volume(int channel, int volume)
```

You can pass in -1 for channel to change all channels' volumes simultaneously. The maximum value for volume is 255, and the minimum is 0

Change the audio panning (volume for each ear) with

```c
void gr_set_panning(int channel, int v_left, int v_right)
```

The maximum value for each ear is 255

The panning can be reset (both ears to maximum) with

```c
void gr_set_mono(int channel)
```

The attenuation (smooth lowering of volume with distance) of a channel can be set and unset with one of these

```c
void gr_set_attenuation(int channel, int distance)
void gr_set_no_attenuation(int channel)
```

# Misc

Set the max number of channels (the max channel id) that can be used with

```c
void gr_set_channel_number(int number)
```