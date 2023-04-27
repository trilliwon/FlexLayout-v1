// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

import UIKit

enum PageType: Int {
    case intro
    case rayWenderlich
    case tableview
    case collectionView
    case exampleColumn
    case pilatesExampleA
    case pilatesExampleB
    case pilatesExampleC
    case pilatesExampleD
    case pilatesExampleE
    case pilatesExampleF
    // case flex
    
    case count
    
    var text: String {
        switch self {
        case .intro:          return "Intro Example"
        case .rayWenderlich:  return "Raywenderlich Tutorial"
        case .tableview:      return "UITableView with variable cell's height"
        case .collectionView: return "UICollectionView with variable cell's height"
        case .exampleColumn:  return "Example 1 - Column"
        case .pilatesExampleA:   return "Pilates C Example"
        case .pilatesExampleB:   return "Pilates Obj-C Example"
        case .pilatesExampleC:   return "Pilates Java Example"
        case .pilatesExampleD:   return "Pilates C# Example"
        case .pilatesExampleE:   return "Pilates Android Example"
        case .pilatesExampleF:   return "Pilates Baseline Example"
        // case .flex:           return "Flexbox"
        case .count:          return ""
        }
    }

    var viewController: UIViewController {
        switch self {
        case .intro:          return IntroViewController(pageType: self)
        case .rayWenderlich:  return RayWenderlichTutorialViewController(pageType: self)
        case .tableview:      return TableViewExampleViewController(pageType: self)
        case .collectionView: return CollectionViewExampleViewController(pageType: self)
        case .exampleColumn:  return Example1ViewController(pageType: self)
        case .pilatesExampleA:   return PilatesExampleAViewController(pageType: self)
        case .pilatesExampleB:   return PilatesExampleBViewController(pageType: self)
        case .pilatesExampleC:   return PilatesExampleCViewController(pageType: self)
        case .pilatesExampleD:   return PilatesExampleDViewController(pageType: self)
        case .pilatesExampleE:   return PilatesExampleEViewController(pageType: self)
        case .pilatesExampleF:   return PilatesExampleFViewController(pageType: self)
        // case .flex:           return FlexboxViewController(pageType: self)
        case .count:          return UIViewController()
        }
    }
}

class MenuViewController: BaseViewController {
    fileprivate var mainView: MenuView {
        return self.view as! MenuView
    }

    override init() {
        super.init()
        title = "FlexLayout Examples"
    }

    required init(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func loadView() {
        view = MenuView()
        mainView.delegate = self
    }
    
//    override func viewDidAppear(_ animated: Bool) {
//        super.viewDidAppear(true)
//        didSelect(pageType: .collectionView)
//    }
}

// MARK: MenuViewDelegate
extension MenuViewController: MenuViewDelegate {
    func didSelect(pageType: PageType) {
        navigationController?.pushViewController(pageType.viewController, animated: true)
    }
}
