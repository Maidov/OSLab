#ifndef ZMQ_STD_HPP
#define ZMQ_STD_HPP

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <zmq.h>

const char* NODE_EXECUTABLE_NAME = "calculation";
const char SENTINEL = '$';
const int PORT_BASE = 8000;
const int WAIT_TIME = 1000; //секунда

enum actions_t {
	fail    = 0,
	success = 1,
	create  = 2,
	bind    = 3,
	ping    = 4,
	exec    = 5,
	info    = 6,
	notfound= 7,
	responce= 8
};

struct node_token_t {
	actions_t action;
	long long parent_id, id;
};

namespace zmq_std {
	void init_pair_socket(void* & context, void* & socket) {
		int rc;
		context = zmq_ctx_new(); // создали контекст
		socket = zmq_socket(context, ZMQ_PAIR); // сокет на прием передачу
		// установка максимального таймаута приема/передачи
		rc = zmq_setsockopt(socket, ZMQ_RCVTIMEO, &WAIT_TIME, sizeof(int)); // параметры приема
		assert(rc == 0); // проверка установки параметров
		rc = zmq_setsockopt(socket, ZMQ_SNDTIMEO, &WAIT_TIME, sizeof(int)); // параметры отправки
		assert(rc == 0);
	}

	template<class T>
	void recieve_msg(T & reply_data, void* socket) {
		int rc = 0;
		zmq_msg_t reply;
		zmq_msg_init(&reply); // инициализировали сообщение
		rc = zmq_msg_recv(&reply, socket, 0); // прием сообщ. без доп. флагов (флаг 0)
		assert(rc == sizeof(T)); // кол-во полученых байтов
		reply_data = *(T*)zmq_msg_data(&reply); // привели к типу Т, разыменовали
		rc = zmq_msg_close(&reply); // закрыли
		assert(rc == 0);
	}

	template<class T>
	void send_msg(T* token, void* socket) {
		int rc = 0;
		zmq_msg_t message;
		zmq_msg_init(&message);
		rc = zmq_msg_init_size(&message, sizeof(T)); // поставили размер даты
		assert(rc == 0); // проверили
		rc = zmq_msg_init_data(&message, token, sizeof(T), NULL, NULL); // внесли данные (NULL - не освобождать память до закрытия)
		assert(rc == 0);
		rc = zmq_msg_send(&message, socket, 0); // отправили (0 - без доп флагов)
		assert(rc == sizeof(T)); // кол-во отправленных байтов
	}

	template<class T>
	bool send_msg_dontwait(T* token, void* socket) {
		int rc;
		zmq_msg_t message;
		zmq_msg_init(&message);
		rc = zmq_msg_init_size(&message, sizeof(T));
		assert(rc == 0);
		rc = zmq_msg_init_data(&message, token, sizeof(T), NULL, NULL);
		assert(rc == 0);
		rc = zmq_msg_send(&message, socket, ZMQ_DONTWAIT); // отправили (ZMQ_DONTWAIT - отправляем не смотря на то что прием занят, если занят то -1)
		if (rc == -1) {
			zmq_msg_close(&message);
			return false;
		}
		assert(rc == sizeof(T));
		return true;
	}

	template<class T>
	bool recieve_msg_wait(T & reply_data, void* socket) {
		int rc = 0;
		zmq_msg_t reply;
		zmq_msg_init(&reply);
		rc = zmq_msg_recv(&reply, socket, 0);
		if (rc == -1) {
			zmq_msg_close(&reply);
			return false;
		}
		assert(rc == sizeof(T));
		reply_data = *(T*)zmq_msg_data(&reply);
		rc = zmq_msg_close(&reply);
		assert(rc == 0);
		return true;
	}

	/* Returns true if T was successfully queued on the socket */
	template<class T>
	bool send_msg_wait(T* token, void* socket) {
		int rc;
		zmq_msg_t message;
		zmq_msg_init(&message);
		rc = zmq_msg_init_size(&message, sizeof(T));
		assert(rc == 0);
		rc = zmq_msg_init_data(&message, token, sizeof(T), NULL, NULL);
		assert(rc == 0);
		rc = zmq_msg_send(&message, socket, 0);
		if (rc == -1) {
			zmq_msg_close(&message);
			return false;
		}
		assert(rc == sizeof(T));
		return true;
	}

	/*
	 * Returns true if socket successfully queued
	 * message and recieved reply
	 */
	template<class T>
	bool send_recieve_wait(T* token_send, T & token_reply, void* socket) {
		if (send_msg_wait(token_send, socket)) {
			if (recieve_msg_wait(token_reply, socket)) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
}

#endif /* ZMQ_STD_HPP */