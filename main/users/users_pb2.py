# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: users.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='users.proto',
  package='users',
  syntax='proto2',
  serialized_options=None,
  serialized_pb=_b('\n\x0busers.proto\x12\x05users\"\xcf\x01\n\x04User\x12\x0f\n\x07\x63hat_id\x18\x01 \x02(\x03\x12\x10\n\x08username\x18\x02 \x01(\t\x12\x10\n\x05privs\x18\x03 \x01(\x05:\x01\x33\x12\x11\n\tlongitude\x18\x04 \x01(\x01\x12\x10\n\x08latitude\x18\x05 \x01(\x01\x12\x18\n\x0bprice_limit\x18\x06 \x01(\x01:\x03\x31.5\x12\x19\n\x0clowest_price\x18\x07 \x01(\x01:\x03\x31.5\x12\x11\n\tfuel_kind\x18\x08 \x01(\x05\x12%\n\x0b\x66uel_prices\x18\t \x03(\x0b\x32\x10.users.FuelPrice\"F\n\tFuelPrice\x12\x0c\n\x04name\x18\x01 \x02(\t\x12\x0e\n\x06street\x18\x02 \x02(\t\x12\x0c\n\x04\x63ity\x18\x03 \x02(\t\x12\r\n\x05price\x18\x04 \x02(\x01\",\n\x0eUserManagement\x12\x1a\n\x05users\x18\x01 \x03(\x0b\x32\x0b.users.User')
)




_USER = _descriptor.Descriptor(
  name='User',
  full_name='users.User',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='chat_id', full_name='users.User.chat_id', index=0,
      number=1, type=3, cpp_type=2, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='username', full_name='users.User.username', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='privs', full_name='users.User.privs', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=3,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='longitude', full_name='users.User.longitude', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='latitude', full_name='users.User.latitude', index=4,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='price_limit', full_name='users.User.price_limit', index=5,
      number=6, type=1, cpp_type=5, label=1,
      has_default_value=True, default_value=float(1.5),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='lowest_price', full_name='users.User.lowest_price', index=6,
      number=7, type=1, cpp_type=5, label=1,
      has_default_value=True, default_value=float(1.5),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='fuel_kind', full_name='users.User.fuel_kind', index=7,
      number=8, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='fuel_prices', full_name='users.User.fuel_prices', index=8,
      number=9, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=23,
  serialized_end=230,
)


_FUELPRICE = _descriptor.Descriptor(
  name='FuelPrice',
  full_name='users.FuelPrice',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='users.FuelPrice.name', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='street', full_name='users.FuelPrice.street', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='city', full_name='users.FuelPrice.city', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='price', full_name='users.FuelPrice.price', index=3,
      number=4, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=232,
  serialized_end=302,
)


_USERMANAGEMENT = _descriptor.Descriptor(
  name='UserManagement',
  full_name='users.UserManagement',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='users', full_name='users.UserManagement.users', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=304,
  serialized_end=348,
)

_USER.fields_by_name['fuel_prices'].message_type = _FUELPRICE
_USERMANAGEMENT.fields_by_name['users'].message_type = _USER
DESCRIPTOR.message_types_by_name['User'] = _USER
DESCRIPTOR.message_types_by_name['FuelPrice'] = _FUELPRICE
DESCRIPTOR.message_types_by_name['UserManagement'] = _USERMANAGEMENT
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

User = _reflection.GeneratedProtocolMessageType('User', (_message.Message,), {
  'DESCRIPTOR' : _USER,
  '__module__' : 'users_pb2'
  # @@protoc_insertion_point(class_scope:users.User)
  })
_sym_db.RegisterMessage(User)

FuelPrice = _reflection.GeneratedProtocolMessageType('FuelPrice', (_message.Message,), {
  'DESCRIPTOR' : _FUELPRICE,
  '__module__' : 'users_pb2'
  # @@protoc_insertion_point(class_scope:users.FuelPrice)
  })
_sym_db.RegisterMessage(FuelPrice)

UserManagement = _reflection.GeneratedProtocolMessageType('UserManagement', (_message.Message,), {
  'DESCRIPTOR' : _USERMANAGEMENT,
  '__module__' : 'users_pb2'
  # @@protoc_insertion_point(class_scope:users.UserManagement)
  })
_sym_db.RegisterMessage(UserManagement)


# @@protoc_insertion_point(module_scope)
