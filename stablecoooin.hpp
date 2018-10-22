/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class [[eosio::contract("stablecoooin")]] stablecoooin : public contract {
public:
      using contract::contract;
      [[eosio::action]]
      void create( name issuer, asset maximum_supply );
      [[eosio::action]]
      void issue( name to, asset quantity, string memo );
      [[eosio::action]]
      void transfer( name from, name to, asset quantity, string memo );
      [[eosio::action]]
      void burn( asset quantity, string memo );
      [[eosio::action]]
      void pause();
      [[eosio::action]]
      void unpause();
      [[eosio::action]]
      void blacklist( name account, string memo );
      [[eosio::action]]
      void unblacklist( name account );

      static asset get_supply( name token_contract_account,  symbol_code sym ) {
            stats statstable( token_contract_account, sym.raw() );
            const auto& st = statstable.get( sym.raw() );
            return st.supply;
      }

      static asset get_balance( name token_contract_account,  name owner, symbol_code sym ) {
            accounts accountstable( token_contract_account, owner.value );
            const auto& ac = accountstable.get( sym.raw() );
            return ac.balance;
      }

private:
      struct [[eosio::table]] account {
            asset       balance;
            uint64_t primary_key()const { return balance.symbol.code().raw(); }
      };

      struct [[eosio::table]] currency_stats {
            asset       supply;
            asset       max_supply;
            name        issuer;
            uint64_t primary_key()const { return supply.symbol.code().raw(); }
      };

      struct [[eosio::table]] blacklist_table {
            name      account;
            auto primary_key() const {  return account.value;  }
      };

      struct [[eosio::table]] pause_table {
            uint64_t            id;
            bool                paused;
            auto primary_key() const {  return id;  }
      };

      typedef eosio::multi_index< "accounts"_n, account > accounts;
      typedef eosio::multi_index< "stat"_n, currency_stats > stats;
      typedef eosio::multi_index< "blacklists"_n, blacklist_table > blacklists;
      typedef eosio::multi_index< "pausetable"_n, pause_table > pausetable;

      void sub_balance( name owner, asset value );
      void add_balance( name owner, asset value, name ram_payer );
      bool is_paused();

      uint64_t const version = 5;
};
