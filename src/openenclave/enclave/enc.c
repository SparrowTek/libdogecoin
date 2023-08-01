// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <stdio.h>

// Include the trusted libdogecoin header that is generated
// during the build. This file is generated by calling the
// sdk tool oeedger8r against the libdogecoin.edl file.
#include "libdogecoin_t.h"

// Include the libdogecoin headher
#include "libdogecoin.h"

// This is the function that the host calls. It prints
// a message in the enclave before calling back out to
// the host to print a message from there too.
void enclave_libdogecoin()
{
    // Print a message from the enclave. Note that this
    // does not directly call fprintf, but calls into the
    // host and calls fprintf from there. This is because
    // the fprintf function is not part of the enclave
    // as it requires support from the kernel.
    fprintf(stdout, "Libdogecoin from the enclave\n");

    // Call back into the host
    oe_result_t result = host_libdogecoin();
    if (result != OE_OK)
    {
        fprintf(
            stderr,
            "Call to host_libdogecoin failed: result=%u (%s)\n",
            result,
            oe_result_str(result));
    }

   // Let's do something with libdogecoin
   dogecoin_ecc_start();

   // establish existing info (utxo is worth 2 doge)
   char *oldPrivKey = "ci5prbqz7jXyFPVWKkHhPq4a9N8Dag3TpeRfuqqC2Nfr7gSqx1fy";
   char *oldPubKey = "031dc1e49cfa6ae15edd6fa871a91b1f768e6f6cab06bf7a87ac0d8beb9229075b";
   char *oldScriptPubKey = "76a914d8c43e6f68ca4ea1e9b93da2d1e3a95118fa4a7c88ac";
   char* utxo_id = "b4455e7b7b7acb51fb6feba7a2702c42a5100f61f61abafa31851ed6ae076074";
   int utxo_vout = 1;
   char* amt_total = "2.0";

   // generate new key pair to send to
   char newPrivKey[53];
   char newPubKey[35];
   generatePrivPubKeypair(newPrivKey, newPubKey, false);

   // build and sign the transaction
   int idx = start_transaction();
   add_utxo(idx, utxo_id, utxo_vout);
   add_output(idx, newPubKey, "0.69");
   finalize_transaction(idx, newPubKey, "0.00226", amt_total, oldPubKey);
   sign_transaction(idx, oldScriptPubKey, oldPrivKey);

   // print result
   printf("\nFinal signed transaction hex: %s\n\n", get_raw_transaction(idx));

   dogecoin_ecc_stop();

}

// Lets try running a function for cli
// start with some calls the cli apps make
// then we'll try and integrate host and cli
void enclave_libdogecoin_generate_mnemonic()
{
    ENTROPY_SIZE size = "256";
    MNEMONIC mnemonic = { 0 };

    dogecoin_ecc_start();

    /* generate mnemonic with entropy out */
    if (generateRandomEnglishMnemonic(size, mnemonic) == -1) {
        dogecoin_ecc_stop();
        return -1;
        }
}