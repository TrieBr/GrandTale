#include "threadRunnable.h"


void* threadProc(ALLEGRO_THREAD* thread, void* arg) {
	threadRunnable* tR = (threadRunnable*)arg;
	tR->initialize();
	while (!al_get_thread_should_stop(thread)) {
		tR->run();
	}
	tR->shutdown();
	return NULL;
}
	threadRunnable::~threadRunnable() {
		al_join_thread(threadHandle,NULL); //Wait for the thread to finish executing
	}
	void threadRunnable::start() {
		threadHandle = al_create_thread(threadProc,this); //Create the thread
		al_start_thread(threadHandle); //Start the thread
	}

	void threadRunnable::stop() {
		al_set_thread_should_stop(threadHandle);
	}


