package com.github.Artem_Pb.exception;

import org.springframework.http.HttpStatus;

public abstract sealed class AppException extends RuntimeException
        permits TaskNotFoundException, InvalidTaskOperationException {
    private final String errorCode;
    private final HttpStatus httpStatus;

    protected AppException(String message, String errorCode, HttpStatus httpStatus) {
        super(message);
        this.errorCode = errorCode;
        this.httpStatus = httpStatus;
    }

    public String getErrorCode() {
        return errorCode;
    }

    public HttpStatus getHttpStatus() {
        return httpStatus;
    }
}
