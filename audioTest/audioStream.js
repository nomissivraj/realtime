const Audio = require('audio');

let audio = Audio.load('./record.mp3', (err, audio) => {
	//repeat slowed down fragment
	audio.write(audio.copy(2.1, 1).scale(.9), 3.1)

	//delete fragment, fade out
	audio.delete(2.4, 2.6).fadeOut(.3, 2.1)

	//insert other fragment not overwriting the existing data
	Audio('./other-record.mp3', (err, otherAudio) => {
		audio.insert(2.4, otherAudio)
	})

	audio.download('edited-record')
});

/*const player = require('play-sound')(opts = {
  player: "C:\\Users\\simon\\Downloads\\mplayer-svn-38117\\mplayer.exe"
});

// $ mplayer
player.play('audio/Ocean-waves.mp3',{volume: 0}, function(err){
  if (err) throw err
});

player.play('audio/atmosphere.mp3', function(err){
  if (err) throw err
});

setInterval(() => {
  player.play('audio/wub.wav', function(err){
    if (err) throw err
  });
}, 3000);

 
/* { timeout: 300 } will be passed to child process
player.play('audioTest.mp3', { timeout: 300 }, function(err){
  if (err) throw err
})
 
 configure arguments for executable if any
player.play('audioTest.mp3', { afplay: ['-v', 1 ] /* lower volume for afplay on OSX *//* }, function(err){
  if (err) throw err
})*/
 
// access the node child_process in case you need to kill it on demand 
/*
var audio = player.play('audioTest.mp3', function(err){
  if (err && !err.killed) throw err
})
audio.kill()*/