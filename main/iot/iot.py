from iot.service.out import libiotservice


def control_shade(id, values):
    return libiotservice.control_shade(id, values)
