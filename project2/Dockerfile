FROM microsoft/dotnet

RUN apt-get update && \
	apt-get upgrade -y && \
	apt-get install -y software-properties-common jq less

RUN apt-add-repository 'deb http://shaggytwodope.github.io/repo ./' -y && \
	apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 7086E9CC7EC3233B && \
	apt-get update

RUN apt-get install -y drive && \
	rm -rf /var/lib/apt/lists/*

WORKDIR /csproj
