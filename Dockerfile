FROM gcc:7.3
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN g++ -o myapp *.cpp
CMD ["./myapp"]