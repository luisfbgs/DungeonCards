// #include "AudioPlayer.h"
// #include <string>
// #include <memory>

// #include "Sound.h"
// #include "Music.h"

// #include <chrono>

// AddrAndTimeStamp::AddrAndTimeStamp(void* callerPtr) {
//     this->obj = (Pointer)callerPtr;
//     this->timeStamp = std::chrono::high_resolution_clock::now();
// }

// bool AddrAndTimeStamp::operator<(const AddrAndTimeStamp& other) {
//     if (this->obj != other.obj) {
//         return this->obj < other.obj;
//     }
//     else {
//         return this->timeStamp < other.timeStamp;
//     }
// }


// PairAddrMusic::PairAddrMusic(void* callerPtr, std::string file) : AddrAndTimeStamp(callerPtr) {
//     this->music.Open(file);
//     this->music.Play();
// }

// PairAddrSound::PairAddrSound(void* callerPtr, std::string file) : 
//     AddrAndTimeStamp(callerPtr){
//     this->sound = new Sound( std::make_shared<GameObject>(), file );
//     this->sound->Open(file);
//     this->sound->Play(0);  // tocar som infinitas vezes
// }

// PairAddrSound::~PairAddrSound() {
//     delete this->sound;
// }

// int AudioPlayer::PlaySound(void* callerPtr, std::string file) {
//     AudioPlayer::soundChannelSet.insert( PairAddrSound(callerPtr, file) );
// }

// // int AudioPlayer::PlaySound(void* callerPtr, std::string file) {
// //     auto sound = Sound(
// //         std::make_shared<GameObject>(), file
// //     );

// //     AudioPlayer::soundChannelSet.insert(  );
// // }

// // void AudioPlayer::Update(int dt) {
// //     (void)dt;

// // }
