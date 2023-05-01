#!/bin/bash

# Assurez-vous que nous avons les arguments requis
if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <principal> <interest_rate> <term_in_years>"
    exit 1
fi

# Parse command line arguments
principal=$1
tauxInteret=$2
dureeAnnuelle=$3

# Calculate monthly interest rate and number of payments
tauxInteretMensuel=$(echo "scale=10; $tauxInteret / (12 * 100)" | bc)
nombrePaiements=$(echo "$dureeAnnuelle * 12" | bc)

# Calculate monthly payment
paiementMensuel=$(echo "scale=2; $principal * $tauxInteretMensuel / (1 - (1 + $tauxInteretMensuel)^(-$nombrePaiements))" | bc)

# Calculate total interest paid
total_interest=$(echo "scale=2; ($paiementMensuel * $nombrePaiements) - $principal" | bc)

# Print results
cowsay "Paiement mensuel: ${paiementMensuel} Total des interets payes : ${total_interest}"