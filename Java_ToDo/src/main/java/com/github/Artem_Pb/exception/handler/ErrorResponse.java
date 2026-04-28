package com.github.Artem_Pb.exception.handler;

import java.time.LocalDateTime;

public record ErrorResponse(String code, String message, LocalDateTime timestamp, String path) {
}
