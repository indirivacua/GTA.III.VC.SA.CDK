AUTHOR:
Allegri32 'ssErgiy'
allegri32en.blogspot.com

INSTALLATION INSTRUCTIONS:
Read 'How To Install.txt' on how to install this library.

OPCODE INSTRUCTIONS:
==========================================================================================================
|0AAC: play_audio_stream_1channel "test.mp3" loop 1 volume 0.5						 |
==========================================================================================================
This opcode requires three parameters: the first one is path of the sound file (must be placed from the root folder, e.g: GTA Root Folder\test.mp3 or GTA Root Folder\CLEO\CLEO_AUDIO\test.mp3), the second parameter is a boolean (sound file will loop?), and the final one is a float (volume of the sound file).

Plays audio files on the first channel.
Supported formats: MP3, MP2, MP1, OGG, WAV, AIFF

==========================================================================================================
|0AAD: stop_audio_stream						 				 |
==========================================================================================================
Stops the audio file from playing. 
NOTE: this opcode can't be used to stop the second channel.

==========================================================================================================
|7AAA: play_mod_music "test.mod"						 			 |
==========================================================================================================
This opcode require one parameter: path of the tracker file (must be placed from the root folder, e.g: GTA Root Folder\test.xm or GTA Root Folder\CLEO\CLEO_AUDIO\test.xm)

Plays tracker audio files.
Supported formats: S3M, XM, MOD, IT, UMX

==========================================================================================================
|7AAB: stop_mod_music						 			 	 	 |
==========================================================================================================
Stops the tracker file from playing.

==========================================================================================================
|7AAC: play_audio_stream_2channel "test.mp3" loop 1 volume 0.5						 |
==========================================================================================================
This opcode requires three parameters: the first one is path of the sound file (must be placed from the root folder, e.g: GTA Root Folder\test.mp3 or GTA Root Folder\CLEO\CLEO_AUDIO\test.mp3), the second parameter is a boolean (sound file will loop?), and the final one is a float (volume of the sound file).

Plays audio files on the second channel (good for sound effects).
Supported formats: MP3, MP2, MP1, OGG, WAV, AIFF
NOTE: the second channel can't be stopped by the 0AAD opcode! Use an empty sound file to stop the sound (without looping!).

==========================================================================================================
|7ABB: set_mod_position 2 2						 				 |
==========================================================================================================
This opcode requires two parameters: the first one is order, and the second one is row.

Sets the playing row and order for tracker files.

==========================================================================================================
|7ABC: set_stream_playing_mode 0									 |
==========================================================================================================
This opcode requires one parameter: mode, 0 = paused, 1 = unpaused.

This opcode sets paused/unpaused status (only first channel).