#pragma once

struct sys_lwmutex_t;

struct sys_lwcond_attribute_t
{
	union
	{
		char name[8];
		u64 name_u64;
	};
};

struct sys_lwcond_t
{
	vm::bptr<sys_lwmutex_t> lwmutex;
	be_t<u32> lwcond_queue;
};

struct Lwcond
{
	SMutex signal;
	SleepQueue m_queue;

	Lwcond(u64 name)
		: m_queue(name)
	{
		signal.initialize();
	}
};

// Aux
s32 lwcond_create(sys_lwcond_t& lwcond, sys_lwmutex_t& lwmutex, u64 name_u64);

// SysCalls
s32 sys_lwcond_create(vm::ptr<sys_lwcond_t> lwcond, vm::ptr<sys_lwmutex_t> lwmutex, vm::ptr<sys_lwcond_attribute_t> attr);
s32 sys_lwcond_destroy(vm::ptr<sys_lwcond_t> lwcond);
s32 sys_lwcond_signal(vm::ptr<sys_lwcond_t> lwcond);
s32 sys_lwcond_signal_all(vm::ptr<sys_lwcond_t> lwcond);
s32 sys_lwcond_signal_to(vm::ptr<sys_lwcond_t> lwcond, u32 ppu_thread_id);
s32 sys_lwcond_wait(vm::ptr<sys_lwcond_t> lwcond, u64 timeout);
