/* wincap.cc -- figure out on which OS we're running. Set the
		capability class to the appropriate values.

   Copyright 2001, 2002, 2003, 2004, 2005 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include "winsup.h"

static NO_COPY wincaps wincap_unknown = {
  lock_file_highword:0x0,
  chunksize:0x0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE,
  is_winnt:false,
  is_server:false,
  access_denied_on_delete:false,
  has_delete_on_close:false,
  has_page_guard:false,
  has_security:false,
  has_security_descriptor_control:false,
  has_get_process_times:false,
  has_lseek_bug:false,
  has_lock_file_ex:false,
  has_signal_object_and_wait:false,
  has_eventlog:false,
  has_ip_helper_lib:false,
  has_set_handle_information:false,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:false,
  has_physical_mem_access:false,
  has_working_copy_on_write:false,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:false,
  has_mmap_alignment_bug:false,
  has_hard_links:false,
  can_open_directories:false,
  has_move_file_ex:false,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:false,
  has_try_enter_critical_section:false,
  has_raw_devices:false,
  has_valid_processorlevel:false,
  has_64bit_file_access:false,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:false,
  needs_memory_protection:false,
  pty_needs_alloc_console:false,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:true,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:true,
  has_null_console_handler_routine:false,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:false
};

static NO_COPY wincaps wincap_95 = {
  lock_file_highword:0x0,
  chunksize:32 * 1024 * 1024,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE,
  is_winnt:false,
  is_server:false,
  access_denied_on_delete:true,
  has_delete_on_close:false,
  has_page_guard:false,
  has_security:false,
  has_security_descriptor_control:false,
  has_get_process_times:false,
  has_lseek_bug:true,
  has_lock_file_ex:false,
  has_signal_object_and_wait:false,
  has_eventlog:false,
  has_ip_helper_lib:false,
  has_set_handle_information:false,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:true,
  altgr_is_ctrl_alt:false,
  has_physical_mem_access:false,
  has_working_copy_on_write:false,
  share_mmaps_only_by_name:true,
  virtual_protect_works_on_shared_pages:false,
  has_mmap_alignment_bug:false,
  has_hard_links:false,
  can_open_directories:false,
  has_move_file_ex:false,
  has_negative_pids:true,
  has_unreliable_pipes:true,
  has_named_pipes:false,
  has_try_enter_critical_section:false,
  has_raw_devices:false,
  has_valid_processorlevel:false,
  has_64bit_file_access:false,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:false,
  needs_memory_protection:false,
  pty_needs_alloc_console:false,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:true,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:true,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:true,
  has_null_console_handler_routine:false,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:false
};

static NO_COPY wincaps wincap_95osr2 = {
  lock_file_highword:0x0,
  chunksize:32 * 1024 * 1024,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE,
  is_winnt:false,
  is_server:false,
  access_denied_on_delete:true,
  has_delete_on_close:false,
  has_page_guard:false,
  has_security:false,
  has_security_descriptor_control:false,
  has_get_process_times:false,
  has_lseek_bug:true,
  has_lock_file_ex:false,
  has_signal_object_and_wait:false,
  has_eventlog:false,
  has_ip_helper_lib:false,
  has_set_handle_information:false,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:true,
  altgr_is_ctrl_alt:false,
  has_physical_mem_access:false,
  has_working_copy_on_write:false,
  share_mmaps_only_by_name:true,
  virtual_protect_works_on_shared_pages:false,
  has_mmap_alignment_bug:false,
  has_hard_links:false,
  can_open_directories:false,
  has_move_file_ex:false,
  has_negative_pids:true,
  has_unreliable_pipes:true,
  has_named_pipes:false,
  has_try_enter_critical_section:false,
  has_raw_devices:false,
  has_valid_processorlevel:false,
  has_64bit_file_access:false,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:false,
  needs_memory_protection:false,
  pty_needs_alloc_console:false,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:true,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:true,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:true,
  has_null_console_handler_routine:false,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:false
};

static NO_COPY wincaps wincap_98 = {
  lock_file_highword:0x0,
  chunksize:32 * 1024 * 1024,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE,
  is_winnt:false,
  is_server:false,
  access_denied_on_delete:true,
  has_delete_on_close:false,
  has_page_guard:false,
  has_security:false,
  has_security_descriptor_control:false,
  has_get_process_times:false,
  has_lseek_bug:true,
  has_lock_file_ex:false,
  has_signal_object_and_wait:false,
  has_eventlog:false,
  has_ip_helper_lib:true,
  has_set_handle_information:false,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:true,
  altgr_is_ctrl_alt:false,
  has_physical_mem_access:false,
  has_working_copy_on_write:false,
  share_mmaps_only_by_name:true,
  virtual_protect_works_on_shared_pages:false,
  has_mmap_alignment_bug:true,
  has_hard_links:false,
  can_open_directories:false,
  has_move_file_ex:false,
  has_negative_pids:true,
  has_unreliable_pipes:true,
  has_named_pipes:false,
  has_try_enter_critical_section:false,
  has_raw_devices:false,
  has_valid_processorlevel:true,
  has_64bit_file_access:false,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:false,
  needs_memory_protection:false,
  pty_needs_alloc_console:false,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:true,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:true,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:true,
  has_null_console_handler_routine:false,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:false
};

static NO_COPY wincaps wincap_98se = {
  lock_file_highword:0x0,
  chunksize:32 * 1024 * 1024,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE,
  is_winnt:false,
  is_server:false,
  access_denied_on_delete:true,
  has_delete_on_close:false,
  has_page_guard:false,
  has_security:false,
  has_security_descriptor_control:false,
  has_get_process_times:false,
  has_lseek_bug:true,
  has_lock_file_ex:false,
  has_signal_object_and_wait:false,
  has_eventlog:false,
  has_ip_helper_lib:true,
  has_set_handle_information:false,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:true,
  altgr_is_ctrl_alt:false,
  has_physical_mem_access:false,
  has_working_copy_on_write:false,
  share_mmaps_only_by_name:true,
  virtual_protect_works_on_shared_pages:false,
  has_mmap_alignment_bug:true,
  has_hard_links:false,
  can_open_directories:false,
  has_move_file_ex:false,
  has_negative_pids:true,
  has_unreliable_pipes:true,
  has_named_pipes:false,
  has_try_enter_critical_section:false,
  has_raw_devices:false,
  has_valid_processorlevel:true,
  has_64bit_file_access:false,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:false,
  needs_memory_protection:false,
  pty_needs_alloc_console:false,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:true,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:true,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:true,
  has_null_console_handler_routine:false,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:false
};

static NO_COPY wincaps wincap_me = {
  lock_file_highword:0x0,
  chunksize:32 * 1024 * 1024,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE,
  is_winnt:false,
  is_server:false,
  access_denied_on_delete:true,
  has_delete_on_close:false,
  has_page_guard:false,
  has_security:false,
  has_security_descriptor_control:false,
  has_get_process_times:false,
  has_lseek_bug:true,
  has_lock_file_ex:false,
  has_signal_object_and_wait:false,
  has_eventlog:false,
  has_ip_helper_lib:true,
  has_set_handle_information:false,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:true,
  altgr_is_ctrl_alt:false,
  has_physical_mem_access:false,
  has_working_copy_on_write:false,
  share_mmaps_only_by_name:true,
  virtual_protect_works_on_shared_pages:false,
  has_mmap_alignment_bug:false,
  has_hard_links:false,
  can_open_directories:false,
  has_move_file_ex:false,
  has_negative_pids:true,
  has_unreliable_pipes:true,
  has_named_pipes:false,
  has_try_enter_critical_section:false,
  has_raw_devices:false,
  has_valid_processorlevel:true,
  has_64bit_file_access:false,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:false,
  needs_memory_protection:false,
  pty_needs_alloc_console:false,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:true,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:true,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:true,
  has_null_console_handler_routine:false,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:false
};

static NO_COPY wincaps wincap_nt3 = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:false,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:false,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:false,
  has_eventlog:true,
  has_ip_helper_lib:false,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:false,
  supports_smp:false,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:false,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:false,
  has_switch_to_thread:false,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:false,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:true
};

static NO_COPY wincaps wincap_nt4 = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:false,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:false,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:true,
  has_eventlog:true,
  has_ip_helper_lib:false,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:false,
  supports_smp:true,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:true,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:false,
  has_switch_to_thread:true,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:false,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:true
};

static NO_COPY wincaps wincap_nt4sp4 = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:false,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:false,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:true,
  has_eventlog:true,
  has_ip_helper_lib:true,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:false,
  supports_smp:true,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:true,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:false,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:false,
  has_switch_to_thread:true,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:false,
  has_extended_priority_class:false,
  has_guid_volumes:false,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:true
};

static NO_COPY wincaps wincap_2000 = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:false,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:true,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:true,
  has_eventlog:true,
  has_ip_helper_lib:true,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:true,
  supports_smp:true,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:true,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:true,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:true,
  has_switch_to_thread:true,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:false,
  start_proc_suspended:false,
  has_extended_priority_class:true,
  has_guid_volumes:true,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:false,
  has_working_virtual_lock:true
};

static NO_COPY wincaps wincap_xp = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:false,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:true,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:true,
  has_eventlog:true,
  has_ip_helper_lib:true,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:true,
  supports_smp:true,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:true,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:true,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:true,
  has_switch_to_thread:true,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:true,
  start_proc_suspended:false,
  has_extended_priority_class:true,
  has_guid_volumes:true,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:true,
  has_working_virtual_lock:true
};

static NO_COPY wincaps wincap_2003 = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:true,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:true,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:true,
  has_eventlog:true,
  has_ip_helper_lib:true,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:true,
  supports_smp:true,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:true,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:true,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:true,
  has_switch_to_thread:true,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:true,
  start_proc_suspended:false,
  has_extended_priority_class:true,
  has_guid_volumes:true,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:true,
  has_working_virtual_lock:true
};

static NO_COPY wincaps wincap_vista = {
  lock_file_highword:UINT32_MAX,
  chunksize:0,
  shared:FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
  is_winnt:true,
  is_server:true,
  access_denied_on_delete:false,
  has_delete_on_close:true,
  has_page_guard:true,
  has_security:true,
  has_security_descriptor_control:true,
  has_get_process_times:true,
  has_lseek_bug:false,
  has_lock_file_ex:true,
  has_signal_object_and_wait:true,
  has_eventlog:true,
  has_ip_helper_lib:true,
  has_set_handle_information:true,
  has_set_handle_information_on_console_handles:true,
  supports_smp:true,
  map_view_of_file_ex_sucks:false,
  altgr_is_ctrl_alt:true,
  has_physical_mem_access:true,
  has_working_copy_on_write:true,
  share_mmaps_only_by_name:false,
  virtual_protect_works_on_shared_pages:true,
  has_mmap_alignment_bug:false,
  has_hard_links:true,
  can_open_directories:true,
  has_move_file_ex:true,
  has_negative_pids:false,
  has_unreliable_pipes:false,
  has_named_pipes:true,
  has_try_enter_critical_section:true,
  has_raw_devices:true,
  has_valid_processorlevel:true,
  has_64bit_file_access:true,
  has_process_io_counters:true,
  supports_reading_modem_output_lines:true,
  needs_memory_protection:true,
  pty_needs_alloc_console:true,
  has_terminal_services:true,
  has_switch_to_thread:true,
  cant_debug_dll_entry:false,
  has_ioctl_storage_get_media_types_ex:true,
  start_proc_suspended:false,
  has_extended_priority_class:true,
  has_guid_volumes:true,
  detect_win16_exe:false,
  has_null_console_handler_routine:true,
  has_disk_ex_ioctls:true,
  has_working_virtual_lock:true
};

wincapc wincap;

void
wincapc::init ()
{
  const char *os;
  bool has_osversioninfoex = false;

  if (caps)
    return;		// already initialized

  memset (&version, 0, sizeof version);
  /* Request simple version info first. */
  version.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
  GetVersionEx (reinterpret_cast<LPOSVERSIONINFO>(&version));

  switch (version.dwPlatformId)
    {
      case VER_PLATFORM_WIN32_NT:
	switch (version.dwMajorVersion)
	  {
	    case 3:
	      os = "NT";
	      caps = &wincap_nt3;
	      break;
	    case 4:
	      os = "NT";
	      if (strcmp (version.szCSDVersion, "Service Pack 4") < 0)
		caps = &wincap_nt4;
	      else
		{
		  caps = &wincap_nt4sp4;
		  if (strcmp (version.szCSDVersion, "Service Pack 6") >= 0)
		    has_osversioninfoex = true;
		}
	      break;
	    case 5:
	      os = "NT";
	      has_osversioninfoex = true;
	      switch (version.dwMinorVersion)
		{
		  case 0:
		    caps = &wincap_2000;
		    break;

		  case 1:
		    caps = &wincap_xp;
		    break;

		  default:
		    caps = &wincap_2003;
		}
	      break;
	    case 6:
	      os = "NT";
	      has_osversioninfoex = true;
	      caps = &wincap_vista;
	      break;
	    default:
	      os = "??";
	      caps = &wincap_unknown;
	      break;
	  }
	break;
      case VER_PLATFORM_WIN32_WINDOWS:
	switch (version.dwMinorVersion)
	  {
	    case 0:
	      os = "95";
	      if (strchr (version.szCSDVersion, 'C'))
		caps = &wincap_95osr2;
	      else
		caps = &wincap_95;
	      break;
	    case 10:
	      os = "98";
	      if (strchr (version.szCSDVersion, 'A'))
		caps = &wincap_98se;
	      else
		caps = &wincap_98;
	      break;
	    case 90:
	      os = "ME";
	      caps = &wincap_me;
	      break;
	    default:
	      os = "??";
	      caps = &wincap_unknown;
	      break;
	  }
	break;
      default:
	os = "??";
	caps = &wincap_unknown;
	break;
    }

  if (has_osversioninfoex)
    {
      /* Request extended version to get server info.
	 Available since NT4 SP6. */
      version.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
      GetVersionEx (reinterpret_cast<LPOSVERSIONINFO>(&version));
      if (version.wProductType != VER_NT_WORKSTATION)
	((wincaps *)this->caps)->is_server = true;
    }

  __small_sprintf (osnam, "%s-%d.%d", os, version.dwMajorVersion,
		   version.dwMinorVersion);
}

void
wincapc::set_chunksize (DWORD nchunksize)
{
  ((wincaps *)this->caps)->chunksize = nchunksize;
}
