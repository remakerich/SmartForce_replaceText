FROM alpine as build-env
RUN apk add --no-cache build-base
WORKDIR /home
COPY main.c .
RUN gcc -o main main.c

FROM alpine
COPY --from=build-env /home/main /home/main
CMD ["/home/main"]