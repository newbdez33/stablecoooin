CPP_IN=stablecoooin
CLEOS=$(CLEOS)
CONTRACT_ACCOUNT=woooooooooop
CLEOS=cleos -u http://api.kylin.alohaeos.com

build:
	eosio-cpp -abigen $(CPP_IN).cpp -o $(CPP_IN).wasm

all: build

deploy: build
	$(CLEOS) set contract $(CONTRACT_ACCOUNT) ../stablecoooin -p woooooooooop

pause:
	$(CLEOS) push action $(CONTRACT_ACCOUNT) pause '{}' -p woooooooooop

transfer:
	$(CLEOS) push action $(CONTRACT_ACCOUNT) transfer '{"from":"woooooooooop", "to":"yoooooooooop",  "quantity":"1.0000 J", "memo":"test"}' -p woooooooooop
	
clean:
	rm -f $(CPP_IN).wast $(CPP_IN).wasm


#cleos -u http://kylin-testnet.jeda.one:8888 push action woooooooooop create '{"issuer":"woooooooooop", "maximum_supply":"100 XT"}' -p woooooooooop