void melodyTick() {
 static bool songReadyToPLayFlag = true;

  // Play the melody
  if (requestPlayMelody && songReadyToPLayFlag) {
    songReadyToPLayFlag = player.pollSong();

    // Repeat the melody in X ms
    //if (!songReadyToPLayFlag) {
    //  melodyRepeatTimeout.setInterval(MELODY_REPEAT_INTERVAL_MS);
    //  melodyRepeatTimeout.start();
    //}
  } else {
    player.silence();
  }

  //if (melodyRepeatTimeout.isReady()) {
  //  melodyRepeatTimeout.stop();
  //  melodyRepeatTimeout.reset();
  //  songReadyToPLayFlag = true;
  //}
}
