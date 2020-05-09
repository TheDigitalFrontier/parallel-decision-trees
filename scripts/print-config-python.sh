echo "============="
echo "HARDWARE INFO"
echo "============="

echo ""
echo "Provider: Amazon Web Services EC2"
echo "Instance type: t2.2xlarge"
echo "Availability zone: us-east-2b"
echo ""

echo "============="
echo "HARDWARE INFO"
echo "============="

echo ""
lscpu
echo ""

echo "======="
echo "OS INFO"
echo "======="

echo ""
cat /etc/os-release
echo ""

echo "=================="
echo "PYTHON ENVIRONMENT"
echo "=================="

echo ""
python3 --version
echo ""

source ../finalproject/bin/activate
pip3 freeze
