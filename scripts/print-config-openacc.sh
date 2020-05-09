echo "============="
echo "HARDWARE INFO"
echo "============="

echo ""
echo "Provider: Amazon Web Services EC2"
echo "Instance type: g3.4xlarge"
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

echo "==============="
echo "GPU INFORMATION"
echo "==============="

echo ""
pgaccelinfo
echo ""

echo "========================"
echo "GCC COMPILER INFORMATION"
echo "========================"

echo ""
gcc --version | head -1
echo ""

echo "========================="
echo "PGCC COMPILER INFORMATION"
echo "========================="

echo ""
pgcc --version | head -2 | tail -1
echo ""
