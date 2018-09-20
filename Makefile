CPP_IN=stablecoooin
CLEOS=$(CLEOS)
CONTRACT_ACCOUNT=stablecoooin
CLEOS=cleos

build:
	eosiocpp -o $(CPP_IN).wast $(CPP_IN).cpp

all: build

deploy: build
	$(CLEOS) set contract $(CONTRACT_ACCOUNT) ../stablecoooin
	
clean:
	rm -f $(CPP_IN).wast $(CPP_IN).wasm
