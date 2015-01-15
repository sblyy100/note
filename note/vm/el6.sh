common="-drive file=el7.img -smp 2,cores=1,threads=1,sockets=2 -m 2048"
net="-netdev tap,ifname=tap0,id=hostnet0,vhost=on,script=/etc/qemu-ifup,downscript=/etc/qemu-ifdown \
    -device virtio-net-pci,netdev=hostnet0,id=virtio-net-pci0"

net1="-netdev tap,ifname=tap0,id=hostnet0,vhost=on,script=/etc/qemu-ifup,downscript=/etc/qemu-ifdown"
kvm_append="-netdev tap,id=hostnet1,vhost=on  \
-device virtio-net-pci,netdev=hostnet1,id=virtio-net-pci1 \
-netdev tap,id=hostnet2,vhost=on  \
-device virtio-net-pci,netdev=hostnet2,id=virtio-net-pci2"
#qemu-kvm  $common $net $kvm_append &
#qemu-kvm  $common $net&
kvm_append=""
start_vm()
{
	local cmd="
	qemu-kvm -name vm1 \
	-drive file=el6.img,if=none,id=drive-virtio-disk1,media=disk,cache=none,snapshot=off,aio=native  \
	-device virtio-blk-pci,drive=drive-virtio-disk1,id=virtio-disk1,bootindex=0  \
	-netdev tap,id=hostnet0,vhost=on,script=/etc/qemu-ifup,downscript=downscript=/etc/qemu-ifdown \
	-device virtio-net-pci,netdev=hostnet0,id=virtio-net-pci0 \
	-smp 2,cores=1,threads=1,sockets=2  \
	$kvm_append \
	-m 4096 >>./ips 2>&1 &"
	eval $cmd

}
setup_env(){
	su
	. /mnt/tests/kernel/networking/common/include.sh
   	vClear
}
ifconfig |grep switch || setup_env
start_vm

