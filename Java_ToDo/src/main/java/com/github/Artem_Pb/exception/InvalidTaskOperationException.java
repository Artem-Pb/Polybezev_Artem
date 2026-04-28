package com.github.Artem_Pb.exception;

import org.springframework.http.HttpStatus;

public final class InvalidTaskOperationException extends AppException{
    public InvalidTaskOperationException(String message) {
        super(message, "INVALID_OPERATION", HttpStatus.BAD_REQUEST);
    }
}
